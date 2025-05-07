#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>

#include "engine.hpp"
#include "input.hpp"

#include "simulation.hpp"

int main() {
    Input::bind("quit", GLFW_KEY_PAUSE);

    Reactor_T reactor;

    while(!Engine.shouldClose()) {
        FrameContext ctx = Engine.beginFrame();

        if(Input::isDown("quit")) {
            std::cout << "Break key was pressed, exiting." << std::endl;
            Engine.setShouldClose(true);
        }

        reactor.tick(ctx.deltaTime);

        double avDeltaTime;
        const std::vector<double>& frameTimes = Engine.getFrameTimes();
        for (const double& frameTime : frameTimes) {
            avDeltaTime += frameTime;
        }
        avDeltaTime /= frameTimes.size();

        size_t count = frameTimes.size();
        float* frameTimesData = new float[count];
        size_t startIndex = Engine.getFrameTimeIndex();

        for (size_t i = 0; i < count; ++i) {
            size_t index = (startIndex + i) % count;
            frameTimesData[i] = static_cast<float>(frameTimes[index]);
        }

        ImGui::Begin("Debug");
        ImGui::Text("FPS: %.1f", 1.0f / avDeltaTime);
        ImGui::Text("Delta Time: %.3f", avDeltaTime);
        ImGui::PlotLines("Frame Times", frameTimesData, frameTimes.size(), 0, nullptr, 0.0f, 0.1f, ImVec2(0, 80));
        ImGui::Text("Width: %d", ctx.width);
        ImGui::Text("Height: %d", ctx.height);
        ImGui::End();

        reactor.render();

        Engine.endFrame();
    }

    return 0;
}