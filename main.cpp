#include "simulation.cpp"

int main() {
   Simulation simulation{welcome()};
   while (true) {
    std::cout << "What do you want to do?\n"<<
    "1-> Evolve populations to t+dt \n"<<
    "2-> Run for selected runtime \n"
    "3-> Return data vector \n"<<
    "4-> Return current populations and X(t), Y(t), H \n"<< 
    "5-> Stop simulation"
    << std::endl;
    int input;
    std::cin >> input;

    switch (input) {
    case '1': {
      simulation.evolve(); 
      break;
    }
    case '2': {
      double t;
      std::cout << "Insert run time " << std::endl;
      std::cin >> t;
      simulation.run(t);
      break;
    }
    case '3': {
      std::vector<Population> data = simulation.return_data();
      std::cout << "X(t) and Y(t) estimations" << std::endl;
      std::for_each(data.begin(), data.end(),
                    [](const Population &P) { print(P); });
      break;                
    case '4': {
      Population P{simulation.return_last_evolve()};
      std::cout << "Preys and predators' estimated population" << std::endl;
      std::cout << "X(t):\t" << P.x << "\nY(t):\t" << P.y <<"\nt = \t" << P.t << "\nH =\t " <<P.H<< std::endl;
      break;              
    }
    case '5': {
      std::cout << "Thank you, bye" << std::endl;
      return 0;
    }
    default:
      std::cout << "Invalid action. Please select again." << std::endl;
    }
  }
}

  return 0;
}
