#pragma once

namespace vsensor {
    class ITemperatureSource {
        public:
            virtual ~ITemperatureSource() = default;

            virtual double current_celsius() = 0;
    };
}