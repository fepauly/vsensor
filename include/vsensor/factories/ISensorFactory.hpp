#pragma once

#include "vsensor/core/ISensor.hpp"
#include "vsensor/core/ITransport.hpp"

#include <memory>

namespace vsensor {
    struct CliConfig;
    
    class ISensorFactory {
        public:
            virtual ~ISensorFactory() = default;
            
            virtual std::shared_ptr<ISensor> create(const CliConfig& config, std::shared_ptr<ITransport> transport) = 0;
    };
}