#include <csignal>
#include <chrono>
#include <thread>
#include <iostream>
#include <memory>
#include <atomic>
#include <condition_variable>
#include <mutex>

#include "vsensor/TemperatureSensor.hpp"
#include "vsensor/SimulatedTemperatureSource.hpp"
#include "vsensor/MQTTTransport.hpp" 

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

    auto source = std::make_unique<SimulatedTemperatureSource>(22.0, 5.0);

    MQTTTransport mqtt;

    TemperatureSensor sensor{std::move(source), mqtt, Unit::Celsius};

    std::cout << "[vsensor] Starting temperature simulation.." << std::endl;
    run_sensor_worker(sensor, std::chrono::seconds{2});

    std::cout << "[vsensor] Stopped." << std::endl;
    return 0;
}