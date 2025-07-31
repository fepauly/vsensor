#include "vsensor/cli/CliParser.hpp"
#include <stdexcept>
#include <cstdlib>

namespace vsensor {
    CliConfig parse_cli(int argc, char** argv) {
        CliConfig cfg;
        CLI::App app{"vsensor – virtual sensor simulator"};

        app.add_option("-i,--interval", cfg.interval_sec, "Read/publish interval in seconds")
                        ->capture_default_str();

        auto* sensor_parent = app.add_subcommand("sensor");
        sensor_parent->require_subcommand(1);

        auto* temperature_cmd = sensor_parent->add_subcommand("temperature")
                        ->description("Simulated temperature sensor");

        double mean = 22.0, amp = 5.0;
        temperature_cmd->add_option("--mean", mean, "Mean temperature")->capture_default_str();
        temperature_cmd->add_option("--amp", amp, "Amplitude")->capture_default_str();

        auto* transport_parent = app.add_subcommand("transport");
        transport_parent->require_subcommand(1);

        auto* mqtt_cmd = transport_parent->add_subcommand("mqtt")
                        ->description("MQTT transport (currently dummy)");

        std::string host = "localhost", topic = "vsensor/temp";
        mqtt_cmd->add_option("--host", host,  "MQTT Broker host")->capture_default_str();
        mqtt_cmd->add_option("--topic", topic,"MQTT topic" )->capture_default_str();

        try {
            app.parse(argc, argv);
        } catch (const CLI::ParseError &e) {
            std::exit(app.exit(e));
        }

        if (temperature_cmd->parsed()) {
            cfg.sensor_name = "simulated-temperature";
            cfg.temperature_mean = mean;
            cfg.temperature_amp = amp;
        }
        
        if (mqtt_cmd->parsed()) {
            cfg.transport_name = "mqtt";
            cfg.mqtt_host = host;
            cfg.mqtt_topic = topic;
        }

        return cfg;
    };
}