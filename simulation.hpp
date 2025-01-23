#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <cmath> // Per log()
#include <iostream>
#include <stdexcept>
#include <vector>

namespace LotkaVolterra {

// Definizione della struttura Population
struct Population {
  double x, y, H;
  double t = 0;

  // Costruttore esplicito per inizializzare tutti i membri
  Population(double x_val = 0.0, double y_val = 0.0, double H_val = 0.0,
             double t_val = 0.0)
      : x(x_val), y(y_val), H(H_val), t(t_val) {}

  // operator / definition
  inline Population operator/(const Population &K) const {
    // Verifica se almeno uno dei componenti di B è zero
    if (K.x == 0) {
      std::cerr << "Error: trying to divide by zero in the x component"
                << std::endl;
      throw std::runtime_error("dividing by 0");
    }
    if (K.y == 0) {
      std::cerr << "Error: trying to divide by zero in the y component"
                << std::endl;

      throw std::runtime_error("dividing by 0");
    }
    return Population(x / K.x, y / K.y);
  }
};

class Simulation {
  // Parametri di simulazione
  double a, b, c, d; // Parametri che influenzano la dinamica
  double newX, newY; // Nuove posizioni dopo l'evoluzione
  double t;          // Tempo attuale
  std::vector<Population>
      data; // Vettore che tiene traccia delle popolazioni evolute
public:
  // Costruttore default
  Simulation(double A, double B, double C, double D, Population i_c);

  // Metodi pubblici
  void evolve();                         // Evolve la simulazione di un passo
  std::vector<Population> run(double t); // Esegui la simulazione per un tempo t
  Population take_last();
  Population reset();
  std::vector<Population> print_data();

  // Calcoli relativi all'equilibrio
  double relative_x() const;
  double relative_y() const;
  double calculate_H(bool useEvolvedValues = false)
      const; // metto false predefinito così se non ho valori validi usa le i_c
};
Simulation welcome();
} // namespace LotkaVolterra
#endif
