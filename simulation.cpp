#include "simulation.hpp"
#include <iomanip> // Per formattare l'output
#include <limits>
#include <string>
namespace LotkaVolterra {

// Costruttore della classe Simulation (abcd minuscoli privati)
Simulation::Simulation(double A, double B, double C, double D, Population i_c)
    : a(A), b(B), c(C), d(D), newX(0.0), newY(0.0), t(0.0) {
  data.push_back(i_c); // Aggiungi la popolazione iniziale al vettore
}

// Metodo per evolvere la simulazione di un dt
void Simulation::evolve() {
  double const dt = 0.001;

  // Assicurati che t parta da 0 se data è vuoto (inizio della simulazione)
  if (data.empty()) {
    t = 0.0; // Imposta il tempo iniziale
  } else {
    // Prendi l'ultimo valore di t
    auto it =
        data.end(); // prendi l'elemento dopo l'ultimo elemento del vettore
    --it;           // Sposta l'iteratore sull'ultimo elemento del vettore
    t = it->t;      // Imposta t all'ultimo valore di t
  }

  auto it = data.end(); // prendi l'elemento dopo l'ultimo elemento del vettore
  --it;                 // Sposta l'iteratore sull'ultimo elemento del vettore
  auto const X = it->x; // chiama X l'x dell'ultimo elemento di data
  auto const Y = it->y;

  // Calcolo delle nuove posizioni
  newX = X + (a - b * Y) * X * dt;
  newY = Y + (c * X - d) * Y * dt;
  // Incrementa il tempo
  t += dt;

    // Controllo che il valore corrente di x e y non sia infinito
  if (std::isinf(newX) || std::isinf(newY)) {
      std::cout << "preys: " << newX << ", predators: " << newY << std::endl;
    throw std::runtime_error("Overflow during simulation.\n");
  }
    
    // Controllo che il valore corrente di x e y non sia negativo
  if (newX <= 0 || newY <= 0) {
      std::cout << "preys: " << newX << ", predators: " << newY << std::endl;
    throw std::runtime_error(
        "The number of preys or predators went down to zero or "
        "less than zero.\n");
  }

  // Calcola H per lo stato corrente
  double newH = -d * log(X) + c * X + b * Y - a * log(Y);
  data.push_back(
      {newX, newY, newH, t}); // Aggiungi il nuovo stato al vettore dei dati
}

// Metodo per eseguire la simulazione per un tempo t
std::vector<Population> Simulation::run(double totalTime) {

  while (true) {

    if (std::cin.fail() || totalTime <= 0) {
      std::cin.clear(); // Rimuove il flag di errore
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n'); // Ignora il resto della riga
      std::cerr << "Input not valid. Please, insert a time interval grater "
                   "than zero: "
                << std::endl;
      std::cin >> totalTime; // Chiede un nuovo input
    } else {
      break; // Uscire dal ciclo quando l'input è valido
    }
  }

  int i = 0;
  while (i != totalTime * 1000) { // Simulazione dt per dt
    evolve();
    ++i;
  }

  return data;
}

// Metodo per calcolare x relativo all'eq
double Simulation::relative_x() const {
  double x_eq = d / c; // Punto di equilibrio per x
  return (x_eq != 0) ? (newX / x_eq) : 0;
}

// Metodo per calcolare y relativo all'eq
double Simulation::relative_y() const {
  double y_eq = a / b; // Punto di equilibrio per y
  return (y_eq != 0) ? (newY / y_eq) : 0;
}

// Metodo per calcolare H
double Simulation::calculate_H(bool useEvolvedValues) const {
  // Se useEvolvedValues è true, usa newX e newY, altrimenti usa i valori
  // iniziali di x e y
  double x_gen = useEvolvedValues
                     ? newX
                     : data.front().x; // Usa newX/newY se useEvolvedValues è
                                       // true, altrimenti usa i valori iniziali
  double y_gen = useEvolvedValues ? newY : data.front().y;

  // Calcola H usando i valori selezionati
  return -d * log(x_gen) + c * x_gen + b * y_gen - a * log(y_gen);
}

Population Simulation::take_last() {
  // Calcola il punto di equilibrio
  const Population eq(d / c, a / b);

  // Prendi l'ultimo stato evolutivo
  const Population &last_state = data.back();

  return Population(last_state.x / eq.x, last_state.y / eq.y, calculate_H(),
                    last_state.t);
}

Population Simulation::reset() {

  const Population &first_state = data.front();

  data.clear();                // Pulisce il vettore data
  data.push_back(first_state); // Aggiungi l'elemento iniziale

  std::cout << "Evolution deleted. Back to initial conditions:" << std::endl;

  return Population(first_state);
}

std::vector<Population> Simulation::print_data() {
  // Calcola il punto di equilibrio
  Population const eq{d / c, a / b};

  // Crea un vettore per i dati normalizzati
  std::vector<Population> norm_data(data.size());

  // Usa std::transform per normalizzare i dati
  std::transform(data.begin(), data.end(), norm_data.begin(),
                 [this, eq](const Population &P) {
                   return Population(P.x / eq.x, P.y / eq.y, calculate_H(),
                                     P.t); // Normalizza ogni elemento di data
                 });

  return norm_data; // Restituisci il vettore normalizzato
}

Simulation welcome() {
  double A = 0.0, B = 0.0, C = 0.0, D = 0.0;
  Population i_c;

  std::cout << "Welcome! This is a simulation of the Lotka-Volterra "
               "model.\nInsert the equation's parameters:\n";

  auto askForValidInput = [](const std::string &prompt, double &value) {
    while (true) {
      std::cout << prompt;
      std::cin >> value; // Legge direttamente un double

      if (std::cin.fail() || value <= 0) {
        std::cin.clear(); // Rimuove il flag di errore
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n'); // Ignora il resto della riga
        std::cerr << "Input not valid. Please enter a number greater than zero."
                  << std::endl;
      } else {
        break; // Esce dal ciclo se l'input è valido
      }
    }
  };

  // Utilizzo della funzione per chiedere l'input per i parametri
  askForValidInput("Preys' reproduction rate A:\t", A);
  askForValidInput("Preys' death rate B:\t\t", B);
  askForValidInput("Predators' reproduction rate C:\t", C);
  askForValidInput("Predators' death rate D:\t", D);

  i_c.t = 0.0; // Inizializza il tempo

  // Chiedi i valori iniziali per la popolazione
  askForValidInput("Number of preys:\t", i_c.x);
  askForValidInput("Number of predators:\t", i_c.y);

  return Simulation(A, B, C, D, i_c);
}
} // namespace LotkaVolterra
