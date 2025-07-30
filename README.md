# vsensor

Virtual sensor CLI application in C++. Developed for usage with the **telemetrix** IoT Dashboard (check out the dashboard [here](https://github.com/fepauly/telemetrix)).

Goal is to replicate real world sensors with different transport protocols, e.g. MQTT.

## 🔧 Features

- Simulated temperature sensor (based on simple sinus curve simulating a day with random noise)
- CLI tool
- Modular and expandable architecure

## Compilation

- C++17 compatible compiler
- CMake >= 3.20
- vcpkg setup

```bash
git clone https://github.com/fepauly/vsensor.git
cd vsensor
cmake -B build -DCMAKE_TOOLCHAIN_FILE=<path/to/vcpkg.cmake>
cmake --build build

# Run vsensor
./build/vsensor_cli
```

## Roadmap

- Temperature sensor with OpenWeaterApi connection
- MQTT implementation
- Possible configurations via CLI arguments
- More sensortypes and transport types