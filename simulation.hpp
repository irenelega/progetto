#ifndef VOLTERRA_HPP
#define VOLTERRA_HPP
#include <algorithm>
#include <iostream>
#include <vector>

struct Coordinates 
{ 
  double X; //number of preys
  double Y; //number of predators
  double H; //integrale primo del moto
  inline Coordinates operator / (const Coordinates &B) const  //perchè solo con B??????? perchè B è un vettore?? e non cte
   {if (B.X == 0 || B.Y == 0) 
     {
      throw std::runtime_error{"Trying to divide by 0"};
     }
    return Coordinates{X / B.X, Y / B.Y, H};
   }
};
class Simulation {
 private:
  // x prede, y predatori
  double current_x, current_y;

  // A: tasso riproduzione prede
  // B: tasso mortalità prede (che probabilità ha ogni predatore di uccidere
  // una preda)
  // C: tasso riproduzione predatori
  // D: tasso mortalità predatori
  double A, B, C, D;

  // Valori di equilibrio
  // (Quando il sistema è in equilibrio, dovrebbero stabilizzarsi a 1)

  // Tempo globale e passo temporale della simulazione
  double t;
  double dt;

 public:
  Simulation(SimulationParameters const& params);

  double get_relative_x() const;
  double get_relative_y() const;
  double get_current_x() const;
  double get_current_y() const;
  double get_H() const;

  void evolve();
  std::string print_info() const;
};












#endif
