#pragma once

#include "vsensor/core/ISensor.hpp"

namespace vsensor {

    class ITransport {
        public:
        virtual ~ITransport() = default;

        virtual void publish(const SensorReading& reading) = 0;
    };
}