#pragma once

#include "vsensor/core/ITemperatureSource.hpp"

#include <random>
#include <chrono>

namespace vsensor {
    class SimulatedTemperatureSource : public ITemperatureSource {
        public:
            SimulatedTemperatureSource(double mean = 22.0, double amplitude = 5.0, unsigned seed = std::random_device{}());

            double current_celsius() override;

        private:
            double m_mean;
            double m_amplitude;
            std::mt19937_64 m_rng;
            std::normal_distribution<double> m_noise{0.0, 0.2};
            std::chrono::system_clock::time_point m_start;
    };
}