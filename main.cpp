#include <iostream>
#include "simulation.cpp"

int main() {
   Simulation simulation=welcome();
   while (true) {
    std::cout << "What do you want to do?\n" <<
    "1-> Evolve populations to t+dt \n" <<
    "2-> Run for selected runtime \n" <<
    "3-> Return data vector \n" <<
    "4-> Return current populations and X(t), Y(t), H \n" <<
    "5-> Stop simulation"
    << std::endl;
    int input;
    std::cin >> input;

    switch (input) {
    case 1: {
      simulation.evolve();
      break;
    }
    case 2: {
      double t;
      std::cout << "For how long do you want to evolve the system?: " << std::endl;
      std::cin >> t;
      simulation.run(t);
      break;
    }
    case 3: {
      std::vector<Population> data = simulation.take_data();
      std::cout << "Preys, predator, and H for each dt" << std::endl;
      for (const auto& P : data) {
          simulation.print(P);  // Passa ogni stato di simulazione a print()
      }
      break;
    }
    case 4: {
      Population P=simulation.take_last();
      std::cout << "Preys and predators' last estimated population" << std::endl;
      std::cout << "X(t):\t" << P.x << "\nY(t):\t" << P.y << "\nH =\t " << P.H << "\nt = \t" << P.t << std::endl;
      break;
    }
    case 5: {
      std::cout << "Thank you, bye." << std::endl;
      return 0;
    }
    default:
      std::cout << "Invalid action. Please select again." << std::endl;
    }
  }
}

