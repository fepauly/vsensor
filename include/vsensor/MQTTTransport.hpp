#pragma once

#include "vsensor/ITransport.hpp"

namespace vsensor {

    class MQTTTransport : public ITransport {
        public:
            MQTTTransport();

            void publish(const SensorReading& reading) override;
    };
}