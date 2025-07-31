#include <csignal>
#include <chrono>
#include <thread>
#include <iostream>
#include <memory>
#include <atomic>
#include <condition_variable>
#include <mutex>

#include "vsensor/sensors/TemperatureSensor.hpp"
#include "vsensor/sensors/SimulatedTemperatureSource.hpp"
#include "vsensor/transport/MQTTTransport.hpp"
#include "vsensor/cli/CliParser.hpp"
#include "vsensor/core/Registry.hpp"
#include "vsensor/factories/ISensorFactory.hpp"
#include "vsensor/factories/ITransportFactory.hpp"
#include "vsensor/factories/TemperatureSensorFactory.hpp"
#include "vsensor/factories/MQTTTransportFactory.hpp"

using namespace vsensor;

namespace {
 
    std::atomic_bool stop_flag{false};

    void signal_handler(int signal) {
        std::cerr << "\n[signal] Caught signal " << signal << ", stopping current process...\n";
        stop_flag.store(true);
    }

    void run_sensor_worker(ISensor& sensor, std::chrono::seconds interval) {
        while (!stop_flag.load()) {
            auto reading = sensor.read();
            std::this_thread::sleep_for(interval);
        }
    }
}

int main(int argc, char** argv) {
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    auto& sensor_registry = Registry<ISensorFactory>::instance();
    auto& transport_registry = Registry<ITransportFactory>::instance();
    
    sensor_registry.register_factory("simulated-temperature", 
        std::make_unique<TemperatureSensorFactory>());
    transport_registry.register_factory("mqtt", 
        std::make_unique<MQTTTransportFactory>());

    // Parse command line arguments
    CliConfig config;
    try {
        config = parse_cli(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing command line: " << e.what() << std::endl;
        return 1;
    }

    // Validate both sensor and transport were specified
    if (config.sensor_name.empty() || config.transport_name.empty()) {
        std::cerr << "[Error] Both sensor and transport subcommands are required" << std::endl;
        return 1;
    }

    // Get transport factory and create transport
    auto* transport_factory = transport_registry.get(config.transport_name);
    if (!transport_factory) {
        std::cerr << "[Error] Unknown transport type: " << config.transport_name << std::endl;
        return 1;
    }
    
    auto transport = transport_factory->create(config);
    if (!transport) {
        std::cerr << "[Error] Failed to create transport" << std::endl;
        return 1;
    }

    // Get sensor factory and create sensor
    auto* sensor_factory = sensor_registry.get(config.sensor_name);
    if (!sensor_factory) {
        std::cerr << "[Error] Unknown sensor type: " << config.sensor_name << std::endl;
        return 1;
    }
    
    auto sensor = sensor_factory->create(config, transport);
    if (!sensor) {
        std::cerr << "[Error] Failed to create sensor" << std::endl;
        return 1;
    }

    std::cout << "[vsensor] Starting " << config.sensor_name << " simulation with " 
              << config.transport_name << " transport (interval: " << config.interval_sec << "s)" << std::endl;
    
    run_sensor_worker(*sensor, std::chrono::seconds{config.interval_sec});

    std::cout << "[vsensor] Stopped." << std::endl;
    return 0;
}