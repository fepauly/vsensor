cmake_minimum_required(VERSION 3.20)
project(vsensor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$HOME/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

find_package(cpr CONFIG REQUIRED)
find_package(PahoMqttCpp CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

add_library(vsensor
    src/TemperatureSensor.cpp
    src/MQTTTransport.cpp
    src/SimulatedTemperatureSource.cpp
)

target_include_directories(vsensor PUBLIC include)
target_link_libraries(vsensor
    PUBLIC
        cpr::cpr
        PahoMqttCpp::paho-mqttpp3
        nlohmann_json::nlohmann_json
)

add_executable(vsensor_cli src/main.cpp)
target_link_libraries(vsensor_cli PRIVATE vsensor cxxopts::cxxopts)