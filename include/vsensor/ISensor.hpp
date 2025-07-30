#pragma once

#include <chrono>
#include <cstdint>

namespace vsensor {

    /* Physical units a sensor can return. */
    enum class Unit {
        // Temperature
        Celsius,
        Fahrenheit,
        Kelvin
    };

    struct SensorReading {
        double value;
        Unit unit;
        std::chrono::system_clock::time_point timestamp;

        static SensorReading now(double v, Unit u) noexcept {
            return {v, u, std::chrono::system_clock::now()};
        }
    };


    class ISensor {
        public:
            virtual ~ISensor() = default;

            [[nodiscard]]
            virtual SensorReading read() = 0;
    };
}