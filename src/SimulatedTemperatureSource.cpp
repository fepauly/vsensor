#include "vsensor/SimulatedTemperatureSource.hpp"

#include <cmath>

namespace vsensor {

    SimulatedTemperatureSource::SimulatedTemperatureSource(double mean, double amp, unsigned seed) 
        : m_mean{mean}, m_amplitude{amp}, m_rng{seed}, m_start{std::chrono::system_clock::now()}
        {}

    double SimulatedTemperatureSource::current_celsius() {
        auto elapsed = std::chrono::duration<double>(std::chrono::system_clock::now() - m_start).count();
        double hours = elapsed / 3600.0;

        constexpr double two_pi = 2.0 * 3.14159;
        double base = m_mean + m_amplitude * std::sin(two_pi * hours / 24.0);
        return base + m_noise(m_rng);
    }
}