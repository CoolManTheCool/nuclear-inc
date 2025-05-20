#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <rolling_buffer.hpp>

#include <string>
#include <vector>

#define AMBIENT_TEMP 20.0

class Reactor_T {
public:
    Reactor_T();

    void render();

    // Gambler's Stuff

    bool coinState = false; // 0 = heads, 1 = tails
    std::vector<bool> coinStateBuffer;
    float balance = 100.0;
    std::vector<float> balanceBuffer{100};
    float bet = 0.0;
    float peak = balance;
    unsigned int heads = 0;

private:
};

#endif // SIMULATION_HPP