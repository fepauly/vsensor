#include "vsensor/TemperatureSensor.hpp"

namespace vsensor {
    TemperatureSensor::TemperatureSensor(std::unique_ptr<ITemperatureSource> source,
                                        ITransport& transport,
                                        Unit out_unit = Unit::Celsius)
        : m_source{std::move(source)}, m_transport{transport}, m_out_unit{out_unit}
    {}

    SensorReading TemperatureSensor::read() {
        const auto now = std::chrono::system_clock::now();
        double temp_c = m_source->current_celsius();

        double temp_out = temp_c; // TODO Conversion of units

        SensorReading reading{temp_out, m_out_unit, now};
        m_transport.publish(reading);

        return reading;
    }
}