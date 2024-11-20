#include <iostream>
int main()
{
  std::string userInput = user_input();
  Simulation simulation(userInput);

  while (true) 
    {
      int command;
      std::cout << "What do you want to do?\n
        1- evolve to t+dt\n
        2- run for selected runtime\n
        3- return data vector\n
        4- return current x, y\n
        5- return H vector\n
        6- stop\n << std::endl;              //CAMBIARE
      std::cin >> command;

        if (command == 1)
      {
        simulation.evolve();
      } else if (command == 2)
      {
        std::cout << "For how long?" << std::endl;
        double t;
        std::cin >> t;
        simulation.run(t);
      } else if (command == 3)
      {
        std::vector<Coordinates> data = simulation.return_data();
        std::cout << "X(t) and Y(t) estimations" << std::endl;
        std::for_each(data.begin(), data.end(), [](const Coordinates &C) {print(C);});
      } else if (command == 4)
      {
        Coordinates C = simulation.return_last_evolve();
        std::cout << "X(t) and Y(t) estimations" << std::endl;
        std::cout << "X(t)\t" << C.X << "\t Y(t) \t" << C.Y << "t = " << C.t << std::endl;
      } else if (command == 5)
      {
        std::vector<double> data_H = simulation.return_H();
        std::cout << "H constant of evolution" << std::endl;
        std::for_each(data_H.begin(), data_H.end(), [](const double &H) { print(H); });
      } else if (command == 6)
      {
        std::cout << "Bye bye" << std::endl;           //CAMBIARE
        return 0;
      } else
      {
        std::cout << "Invalid action. Please select again." << std::endl;    //CAMBIARE
      }





        
    }

  return 0;
}
