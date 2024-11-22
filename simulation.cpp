#include "simulation.hpp"

#include "Simulation.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iomanip>

void check_parameters(SimulationParameters const& parameters) {
    if (A_ <= 0 || B_ <= 0 || C_ <= 0 || D <= 0 || parameters.initial_x < 0 || parameters.initial_y < 0 || parameters.dt <= 0)
    { // Checking for valid input parameters
    throw std::runtime_error{"Non valid parameters"};
    }
}




