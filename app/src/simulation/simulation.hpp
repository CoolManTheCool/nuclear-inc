#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <rolling_buffer.hpp>

#include <string>

#define AMBIENT_TEMP 20.0

class Reactor_T {
public:
    Reactor_T();
    void tick(double deltaTime);

    void render();

    std::string temperature(double reading);
    
    // User Controls
    float ctrlRodDepth = 1.0f;
    float coolantFlow = 0.0f;

    // User Readings
    double irradiation = 0.0;
    double coolantTemp = AMBIENT_TEMP;
    double powerOutput = 0.0;

    double powerGenerated = 0.0;
    
    bool celcius = false;
private:
    RollingBuffer<double> coolantTempBuffer{300};
    RollingBuffer<double> irradiationBuffer{300};
    
};

#endif // SIMULATION_HPP