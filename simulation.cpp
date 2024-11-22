#include "simulation.hpp"

#include "Simulation.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iomanip>

void check_parameters(SimulationParameters const& params) {
    if (A_ <= 0 || B_ <= 0 || C_ <= 0 || D <= 0 || params.initial_x < 0 || params.initial_y < 0 || params.dt <= 0)
    { // Checking for valid input parameters
    throw std::runtime_error{"Non valid parameters"};
    }
}




