#include "vsensor/factories/TemperatureSensorFactory.hpp"
#include "vsensor/sensors/TemperatureSensor.hpp"
#include "vsensor/sensors/SimulatedTemperatureSource.hpp"
#include "vsensor/cli/CliParser.hpp"

using namespace vsensor;

std::shared_ptr<ISensor> TemperatureSensorFactory::create(const CliConfig& config, 
                                                         std::shared_ptr<ITransport> transport) {
    auto src = std::make_unique<SimulatedTemperatureSource>(config.temperature_mean, config.temperature_amp);
    return std::make_shared<TemperatureSensor>(std::move(src), transport, Unit::Celsius);
}