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
  inline Coordinates operator / (const Coordinates &B) const 
   {if (B.X == 0 || B.Y == 0) 
     {
      throw std::runtime_error{"Trying to divide by 0"};
     }
    return Coordinates{X / B.X, Y / B.Y, t};
   }
};
  class Simulation {
  const double A_;                // par 1
  const double B_;                // par 2
  const double C_;                // par 3
  const double D_;                // par 4
  std::vector<Coordinates> data_; // vector to save the evolution data
public:
  // Default constructor, ensures that t is set to 0
  Simulation(double A, double B, double C, double D, Coordinates CI);

  void evolve();
  std::vector<Coordinates> run(double t);
  Coordinates return_last_evolve();
  std::vector<double> return_H();
  std::vector<Coordinates> return_data();
};









#endif
