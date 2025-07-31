#include "vsensor/factories/MQTTTransportFactory.hpp"
#include "vsensor/transport/MQTTTransport.hpp"
#include "vsensor/cli/CliParser.hpp"

using namespace vsensor;

std::shared_ptr<ITransport> MQTTTransportFactory::create(const CliConfig& config) {
    return std::make_shared<MQTTTransport>();
}