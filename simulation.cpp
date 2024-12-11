#include "simulation.hpp"
#include <iomanip> // Per formattare l'output
#include <limits>
#include <string>

// Costruttore della classe Simulation (abcd minuscoli privati)
Simulation::Simulation(double A, double B, double C, double D, Population i_c)
    : a(A), b(B), c(C), d(D), newX(0.0), newY(0.0), t(0.0) {
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
  askForValidInput("A: ", a);
  askForValidInput("B: ", b);
  askForValidInput("C: ", c);
  askForValidInput("D: ", d);

  i_c.t = 0.0; // Inizializza il tempo

  // Chiedi i valori iniziali per la popolazione
  askForValidInput("Number of preys: ", i_c.x);
  askForValidInput("Number of predators: ", i_c.y);

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

  std::cout << "Starting simulation in t = " << t << std::endl;

  auto it = data.end(); // prendi l'elemento dopo l'ultimo elemento del vettore
  --it;                 // Sposta l'iteratore sull'ultimo elemento del vettore
  auto const X = it->x; // chiama X l'x dell'ultimo elemento di data
  auto const Y = it->y;

  // Calcolo delle nuove posizioni
  newX = X + (a - b * Y) * X * dt;
  newY = Y + (c * X - d) * Y * dt;
  // Incrementa il tempo
  t += dt;

  // Controllo che il valore corrente di x e y non sia negativo
  if (newX <= 0 || newY <= 0) {
    std::cerr << "Error: the number of preys or predators went down to zero or "
                 "less than zero.\n";
    throw std::runtime_error("x or y =0");
  }

  // Controllo che il valore corrente di x e y non sia infinito
  if (std::isinf(newX) || std::isinf(newY)) {
    std::cerr << "Error: overflow during simulation.\n";
    throw std::runtime_error("overflow");
  }

  // Calcola H per lo stato corrente
  double newH = -d * log(X) + c * X + b * Y - a * log(Y);
  data.push_back(
      {newX, newY, newH, t}); // Aggiungi il nuovo stato al vettore dei dati
  std::cout << "x = " << newX << "\ty = " << newY << "\tH = " << newH
            << "\tt = " << t << std::endl;
  std::cout << "x_rel = " << relative_x() << "\ty_rel = " << relative_y()
            << std::endl;
  std::cout << std::endl;
}

// Metodo per eseguire la simulazione per un tempo t
std::vector<Population> Simulation::run(double totalTime) {

  while (totalTime <= 0) {

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

std::vector<Population> Simulation::take_data() {
  // Calcola il punto di equilibrio una volta per tutte
  const Population eq(a / c, a / b);

  if (c == 0 || b == 0) {
    std::cerr << "Error: invalid equilibrium point calculation." << std::endl;
    throw std::runtime_error("dividing by 0");
  }

  // Crea un nuovo vettore per i dati normalizzati
  std::vector<Population> normalized(data.size());

  // Usa std::transform per normalizzare i dati
  std::transform(data.begin(), data.end(), normalized.begin(),
                 [eq](const Population &P) { return P / eq; });

  return normalized;
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
  std::cout << "x(" << first_state.t << ")=\t" << first_state.x << "\ny("
            << first_state.t << ")=\t" << first_state.y << "\nH =\t "
            << calculate_H() << "\nt = \t" << first_state.t << std::endl;

  return Population(first_state);
}

Simulation welcome() {
  double A = 0.0, B = 0.0, C = 0.0, D = 0.0;
  Population i_c;

  std::cout << "Welcome! This is a simulation of the Lotka-Volterra "
               "model.\nInsert the equation's parameters:\n";

  return Simulation(A, B, C, D, i_c);
}
