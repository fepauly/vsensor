#pragma once

#include "vsensor/core/ITransport.hpp"

#include <memory>

namespace vsensor {
    struct CliConfig;
    
    class ITransportFactory {
        public:
            virtual ~ITransportFactory() = default;

            virtual std::shared_ptr<ITransport> create(const CliConfig& config) = 0;
    };
}
