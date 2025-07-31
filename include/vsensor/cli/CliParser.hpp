#pragma once

#include "vsensor/core/Registry.hpp"
#include "vsensor/factories/ISensorFactory.hpp"
#include "vsensor/factories/ITransportFactory.hpp"

#include <CLI/CLI.hpp>
#include <memory>

namespace vsensor {
    struct CliConfig {
        std::string sensor_name;
        std::string transport_name;
        int interval_sec = 2;
        
        double temperature_mean = 22.0;
        double temperature_amp = 5.0;
        
        std::string mqtt_host = "localhost";
        std::string mqtt_topic = "vsensor/temp";
    };

    CliConfig parse_cli(int argc, char** argv);
}