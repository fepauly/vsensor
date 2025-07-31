#pragma once

#include "vsensor/factories/ISensorFactory.hpp"

namespace vsensor {
    class TemperatureSensorFactory : public ISensorFactory {
    public:
        std::shared_ptr<ISensor> create(const CliConfig& config, 
                                       std::shared_ptr<ITransport> transport) override;
    };
}
