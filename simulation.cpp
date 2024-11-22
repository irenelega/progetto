#include "simulation.hpp"

#include "Simulation.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

void check_parameters(SimulationParameters const& params) {
  if (params.initial_x < 0) {
    std::cerr << "Il numero iniziale di prede deve essere >= 0" << std::endl;
    throw std::invalid_argument("Invalid parameter value initial_x");
  }

  if (params.initial_y < 0) {
    std::cerr << "Il numero iniziale di predatori deve essere >= 0"
              << std::endl;
    throw std::invalid_argument("Invalid parameter value initial_y");
  }

  if (params.A <= 0) {
    std::cerr << "Il parametro A deve essere > 0" << std::endl;
    throw std::invalid_argument("Invalid parameter value A");
  }

  if (params.B <= 0) {
    std::cerr << "Il parametro B deve essere > 0" << std::endl;
    throw std::invalid_argument("Invalid parameter value B");
  }

  if (params.C <= 0) {
    std::cerr << "Il parametro C deve essere > 0" << std::endl;
    throw std::invalid_argument("Invalid parameter value C");
  }

  if (params.D <= 0) {
    std::cerr << "Il parametro D deve essere > 0" << std::endl;
    throw std::invalid_argument("Invalid parameter value D");
  }

  if (params.dt <= 0) {
    std::cerr << "Il passo temporale dt deve essere > 0" << params.dt
              << std::endl;
    throw std::invalid_argument("Invalid parameter value dt");
  }
}


#include <cmath>
#include <iomanip>
