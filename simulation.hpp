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
    return Coordinates{X / B.X, Y / B.Y, t};
   }
};











#endif
