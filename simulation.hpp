#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <stdexcept>
#include <cmath>  // Per log()

// Definizione della struttura Population
struct Population {
    double x, y, H;
    double t{0};
};

class Simulation {
    // Parametri di simulazione
    double a, b, c, d;  // Parametri che influenzano la dinamica
    double newX, newY;  // Nuove posizioni dopo l'evoluzione
    double t;  // Tempo attuale
    std::vector<Population> data;  // Vettore che tiene traccia delle popolazioni evolute
public:
    // Costruttore default
    Simulation(double A, double B, double C, double D, Population i_c);

    // Metodi pubblici
    void evolve();  // Evolve la simulazione di un passo
    std::vector<Population> run(double t);  // Esegui la simulazione per un tempo t
    void print() const;  // Stampa i dati correnti
    Population take_last();
    std::vector<Population> take_data();

    // Calcoli relativi all'equilibrio
    double relative_x() const;
    double relative_y() const;
    double calculate_H() const;
};

#endif









#endif
