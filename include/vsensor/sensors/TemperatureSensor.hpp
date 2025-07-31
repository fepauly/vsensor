#pragma once

#include "vsensor/core/ISensor.hpp"
#include "vsensor/core/ITransport.hpp"
#include "vsensor/core/ITemperatureSource.hpp"

#include <chrono>
#include <random>
#include <memory>

namespace vsensor {
    
    class TemperatureSensor : public ISensor {
        public:
            TemperatureSensor(std::unique_ptr<ITemperatureSource> source,
                            std::shared_ptr<ITransport> transport,
                            Unit out_unit);

            [[nodiscard]] 
            SensorReading read() override;

        private:
            std::unique_ptr<ITemperatureSource> m_source;
            std::shared_ptr<ITransport> m_transport;
            Unit m_out_unit;
    };
}