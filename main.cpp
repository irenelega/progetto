#include "simulation.cpp"

int main() {
  Simulation simulation = welcome();
  while (true) {
    std::cout
        << "What do you want to do?\n"
        << "1-> Evolve populations to t+dt \n"
        << "2-> Evolve populations for selected runtime \n"
        << "3-> Return current normalized populations x(t), y(t), and H, t \n"
        << "4-> Restart simulation and go back to initial conditions \n"
        << "5-> Stop simulation" << std::endl;
    int input;
    std::cin >> input;

    switch (input) {
    case 1: {
      simulation.evolve();
      break;
    }
    case 2: {
      double t;
      std::cout << "For how long do you want to evolve the system?: "
                << std::endl;
      std::cin >> t;
      simulation.run(t);
      break;
    }
    case 3: {
      Population P = simulation.take_last();
      std::cout << "Preys and predators' last estimated population"
                << std::endl;
      std::cout << "x_rel(" << P.t << ")=\t" << P.x << "\ny_rel(" << P.t
                << ")=\t" << P.y << "\nH =\t" << P.H << "\nt = \t" << P.t
                << std::endl;
      break;
    }
    case 4: {
      simulation.reset();
      break;
    }
    case 5: {
      std::cout << "Thank you, bye." << std::endl;
      return 0;
    }
    default: {
      if (std::cin.fail() || input < 1 || input > 5) {
        std::cin.clear(); // Rimuove il flag di errore
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n'); // Ignora il resto della riga
        std::cerr << "Input not valid. Please, insert a number from 1 to 5."
                  << std::endl;
      }
    }
    }
  }
}
