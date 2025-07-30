#include "vsensor/MQTTTransport.hpp"

#include <iostream>

namespace vsensor {
  MQTTTransport::MQTTTransport(){};
  
  void MQTTTransport::publish(const SensorReading& reading) {
    std::cout << "Value: " << reading.value << std::endl;  
  }
} 