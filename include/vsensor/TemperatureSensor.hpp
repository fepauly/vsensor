#pragma once

#include "vsensor/ISensor.hpp"
#include "vsensor/ITransport.hpp"
#include "vsensor/ITemperatureSource.hpp"

#include <chrono>
#include <random>
#include <memory>

namespace vsensor {
    
    class TemperatureSensor : public ISensor {
        public:
            TemperatureSensor(std::unique_ptr<ITemperatureSource> source,
                            ITransport& transport,
                            Unit out_unit);

            [[nodiscard]] 
            SensorReading read() override;

        private:
            std::unique_ptr<ITemperatureSource> m_source;
            ITransport& m_transport;
            Unit m_out_unit;
    };
}