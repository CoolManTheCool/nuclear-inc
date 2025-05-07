#include "simulation.hpp"

#include "imgui.h"

#include "input.hpp"

std::string Reactor_T::temperature(double reading) {
    return celcius ? std::to_string(reading) + "°C" : std::to_string((reading * 9.0 / 5.0) + 32.0) + "°F";
}

Reactor_T::Reactor_T() {
    // Input::bind("name", GLFW_KEY_<key>);
    //Input::bind("ctlRodUp", GLFW_KEY_UP);
}

void Reactor_T::tick(double deltaTime) {
    irradiation += (ctrlRodDepth - 0.5) * -0.1 * deltaTime * (irradiation + 100);
    irradiation = std::max(irradiation, 0.0);

    coolantTemp += irradiation * 0.01 * deltaTime;
    coolantTemp -= coolantFlow * (coolantTemp - AMBIENT_TEMP) * 0.05 * deltaTime;

    powerOutput = (coolantTemp - AMBIENT_TEMP) * coolantFlow;

    powerGenerated += powerOutput * deltaTime;

    // Add the new temperature to the buffer
    coolantTempBuffer.add(coolantTemp);
    irradiationBuffer.add(irradiation);
}

void plotDouble(const char* label, RollingBuffer<double>& buffer, double min = 0.0, double max = 160.0) {
    auto orderedArray = buffer.getOrderedArray(); // Get ordered data
    size_t count = buffer.getCount(); // Get the number of elements

    if (orderedArray) {
        // Create a temporary array to hold the float values
        std::vector<float> floatArray(count);
        
        // Convert each double value in orderedArray to float
        for (size_t i = 0; i < count; ++i) {
            floatArray[i] = static_cast<float>(orderedArray[i]);  // Convert to float
        }

        // Plot the data as floats
        ImGui::PlotLines(label, floatArray.data(), count, 0, nullptr, min, max, ImVec2(0, 100));
    }
}

void Reactor_T::render() {
    // Render the reactor state
    ImGui::Begin("Reactor Control");
    
    // Sliders for control rod and fuel rod depth
    ImGui::SliderFloat("Control Rod Depth", &ctrlRodDepth, 0.0f, 1.0f);
    ImGui::SliderFloat("Coolant Flow", &coolantFlow, 0.0f, 1.0f);
    
    // Display coolant flow and temperature
    ImGui::Text("Coolant Flow: %.2f", coolantFlow);
    ImGui::Text(("Coolant Temperature: " + temperature(coolantTemp)).c_str());
    ImGui::Text("Irradiation: %.2f", irradiation);
    ImGui::Text("Power Output: %.2f", powerOutput);
    ImGui::Text("Power Generated: %.2f", powerGenerated);
    // Convert the buffer from double to float for PlotLines
    
    plotDouble("Coolant Temperature", coolantTempBuffer);
    plotDouble("Irradiation", irradiationBuffer, 0.0f, 10000.0f);

    ImGui::End();
}