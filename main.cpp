#include "simulation.hpp"
using namespace LotkaVolterra;
int main() {
  Simulation simulation = welcome();
  while (true) {
    std::cout
        << "What do you want to do?\n"
        << "1-> Evolve populations to t+dt \n"
        << "2-> Evolve populations for selected runtime \n"
        << "3-> Return current normalized populations x(t), y(t), and H, t \n"
        << "4-> Print each evolution's dt \n"
        << "5-> Restart simulation and go back to initial conditions \n"
        << "6-> Stop simulation" << std::endl;
    int input;
    std::cin >> input;

    switch (input) {
    case 1: {
      try {
        simulation.evolve();
      } catch (const std::runtime_error &e) {
        // Gestione dell'eccezione per i valori negativi
        if (std::string(e.what()).find("the number of preys or predators went "
                                       "down to zero or less than zero") !=
            std::string::npos) {
          std::cerr << "Error: " << e.what() << std::endl;
        } else if (std::string(e.what()).find("overflow during simulation") !=
                   std::string::npos) {
          std::cerr << "Error: " << e.what() << std::endl;
        }
      }
      break;
    }
    case 2: {
      double t;
      std::cout << "For how long do you want to evolve the system? "
                << std::endl;
      std::cin >> t;
      try {
        simulation.run(t);
      } catch (const std::runtime_error &e) {
        // Gestione dell'eccezione per i valori negativi
        if (std::string(e.what()).find("the number of preys or predators went "
                                       "down to zero or less than zero.") !=
            std::string::npos) {
          std::cerr << "Error: " << e.what() << std::endl;
        } else if (std::string(e.what()).find("overflow during simulation.") !=
                   std::string::npos) {
          std::cerr << "Error: " << e.what() << std::endl;
        }
      }
      break;
    }
    case 3: {
      Population P = simulation.take_last();
      std::cout << "Preys and predators' last estimated population:"
                << std::endl;
      std::cout << "t = " << P.t << "\t\t"
                << "x_rel = " << P.x << "\t\t"
                << "y_rel = " << P.y << "\t\t"
                << "H = " << P.H << std::endl;
      break;
    }
    case 4: {
      std::cout << "Preys and predators' estimated population for each dt:"
                << std::endl;
      std::vector<Population> data = simulation.print_data();
      std::for_each(data.begin(), data.end(), [](const Population &P) {
        std::cout << "t = " << P.t << "\t\t"
                  << "x_rel = " << P.x << "\t\t"
                  << "y_rel = " << P.y << "\t\t"
                  << "H = " << P.H << std::endl;
      });
      break;
    }
    case 5: {
      simulation.reset();
      std::cout << "Evolution deleted. Back to initial conditions."
                << std::endl;
      break;
    }
    case 6: {
      std::cout << "Thank you, bye." << std::endl;
      return 0;
    }
    default: {
      if (std::cin.fail() || input < 1 || input > 5) {
        std::cin.clear(); // Rimuove il flag di errore
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n'); // Ignora il resto della riga
        std::cerr << "Input not valid. Please, insert a number from 1 to 5:"
                  << std::endl;
      }
    }
    }
  }
}
