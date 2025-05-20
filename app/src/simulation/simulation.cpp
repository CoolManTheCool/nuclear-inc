#include "simulation.hpp"

#include "imgui.h"

#include "input.hpp"

#include <iostream>
#include <vector>

Reactor_T::Reactor_T() {
    srand(time(0));
}

void Reactor_T::render() {

    ImGui::Begin("Coin Flip Simulation");

    ImGui::SliderFloat("Bet Amount", &bet, 0.0f, balance*0.9);
    if (bet > balance) {
        bet = balance * 0.9;
    }
    ImGui::Text("Balance: %.2f", balance);
    ImGui::Text("Coin State: %s", coinState ? "Heads" : "Tails");

    if(ImGui::Button("Flip", ImVec2(128, 64))) {
        coinState = rand() % 2;
        coinStateBuffer.push_back(coinState);
        balance += coinState ? bet : -bet;
        balanceBuffer.push_back(balance);
        if (balance > peak) {
            peak = balance;
        }
        heads += coinState;
    }

    std::vector<float> plotData(coinStateBuffer.begin(), coinStateBuffer.end());
    ImGui::PlotLines("Coin State", plotData.data(), plotData.size(), 0, nullptr, 0.0f, 1.0f, ImVec2(0, 100));
    ImGui::PlotLines("Balance", balanceBuffer.data(), balanceBuffer.size(), 0, nullptr, 0.0f, peak, ImVec2(0, 100));
    ImGui::Text("Heads: %u", heads);
    ImGui::Text("Tails: %u", (unsigned int) coinStateBuffer.size() - heads);
    ImGui::Text("Heads Tails Ratio: %.2f", static_cast<float>(heads) / (coinStateBuffer.size() - heads));
    ImGui::Text("Heads Rails Differnce: %u", abs(heads - (coinStateBuffer.size() - heads)));
    ImGui::End();
}