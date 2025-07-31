#pragma once

#include "vsensor/factories/ITransportFactory.hpp"

namespace vsensor {
    class MQTTTransportFactory : public ITransportFactory {
    public:
        std::shared_ptr<ITransport> create(const CliConfig& config) override;
    };
}
