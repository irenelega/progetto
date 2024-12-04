#include "simulation.hpp"
#include <iostream>
#include <iomanip>  // Per formattare l'output

// Costruttore della classe Simulation (abcd minuscoli privati)
Simulation::Simulation(double A, double B, double C, double D, Population i_c) : a(A), b(B), c(C), d(D), newX(0.0), newY(0.0), t(0.0) // Inizializzo anche newX, newY, t
{
    while (a <= 0) {
        std::cout << "Please, insert a value of A grater than zero: ";
        std::cin >> a;  // Chiede un nuovo input

        // Controlla se l'input è valido
        if (std::cin.fail() || a <= 0) {
            std::cin.clear(); // Rimuove il flag di errore
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora il resto della riga
            std::cerr << "Input not valid." << std::endl;
        } else {
            break; // Uscire dal ciclo quando l'input è valido
            }
    }
     
     while (b <= 0) {
        std::cout << "Please, insert a value of B grater than zero: ";
        std::cin >> b;  // Chiede un nuovo input

            // Controlla se l'input è valido
        if (std::cin.fail() || b <= 0) {
            std::cin.clear(); // Rimuove il flag di errore
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora il resto della riga
            std::cerr << "Input not valid." << std::endl;
            } else {
                break; // Uscire dal ciclo quando l'input è valido
            }
    }
     
    while (c <= 0) {
        std::cout << "Please, insert a value of C grater than zero: ";
        std::cin >> c;  // Chiede un nuovo input

        // Controlla se l'input è valido
        if (std::cin.fail() || c <= 0) {
            std::cin.clear(); // Rimuove il flag di errore
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora il resto della riga
            std::cerr << "Input not valid." << std::endl;
        } else {
            break; // Uscire dal ciclo quando l'input è valido
        }
      
    }
      
    while (d <= 0) {
        std::cout << "Please, insert a value of D grater than zero: ";
        std::cin >> d;  // Chiede un nuovo input

        // Controlla se l'input è valido
        if (std::cin.fail() || d <= 0) {
            std::cin.clear(); // Rimuove il flag di errore
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora il resto della riga
            std::cerr << "Input not valid." << std::endl;
        } else {
            break; // Uscire dal ciclo quando l'input è valido
            }
    }

    i_c.t = 0.0;  // Inizializza il tempo

    
         while (i_c.x <= 0) {
            std::cout << "Please, insert a number of preys grater than zero: ";
            std::cin >> i_c.x;  // Chiede un nuovo input

            // Controlla se l'input è valido
            if (std::cin.fail() || i_c.x <= 0) {
                std::cin.clear(); // Rimuove il flag di errore
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora il resto della riga
                std::cerr << "Input not valid." << std::endl;
            } else {
                break; // Uscire dal ciclo quando l'input è valido
            }
        }
    
    
         while (i_c.y <= 0) {
            std::cout << "Please, insert a number of predators grater than zero: ";
            std::cin >> i_c.y;  // Chiede un nuovo input

            // Controlla se l'input è valido
            if (std::cin.fail() || i_c.y <= 0) {
                std::cin.clear(); // Rimuove il flag di errore
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora il resto della riga
                std::cerr << "Input not valid." << std::endl;
            } else {
                break; // Uscire dal ciclo quando l'input è valido
            }
        }
    
    data.push_back(i_c);  // Aggiungi la popolazione iniziale al vettore
}

// Metodo per evolvere la simulazione di un dt
void Simulation::evolve() {
    double const dt=0.001;

    // Assicurati che t parta da 0 se data è vuoto (inizio della simulazione)
    if (data.empty()) {
        t = 0.0; // Imposta il tempo iniziale
    } else {
        // Prendi l'ultimo valore di t
        auto it = data.end();   // prendi l'elemento dopo l'ultimo elemento del vettore
        --it;                   // Sposta l'iteratore sull'ultimo elemento del vettore
        t = it->t;              // Imposta t all'ultimo valore di t
    }

    std::cout << "Before evolve: t = " << t << std::endl;

    auto it = data.end(); //prendi l'elemento dopo l'ultimo elemento del vettore
    --it;  // Sposta l'iteratore sull'ultimo elemento del vettore
    auto const X = it->x; //chiama X l'x dell'ultimo elemento di data
    auto const Y = it->y;

    // Calcolo delle nuove posizioni
    newX = X + (a - b * Y) * X * dt;
    newY = Y + (c * X - d) * Y * dt;
    // Incrementa il tempo
    t += dt;

    // Calcola H per lo stato corrente
    double newH = -d * log(X) + c * X + b * Y - a * log(Y);
    data.push_back({newX, newY, newH, t});  // Aggiungi il nuovo stato al vettore dei dati
    std::cout << newX << "\t" << newY << "\t" <<  newH << "\t" << t << std::endl;
}

// Metodo per eseguire la simulazione per un tempo t
std::vector<Population> Simulation::run(double totalTime) {
    
        while (totalTime<=0) {
            std::cout << "Please, insert a time interval grater than zero:  ";
            std::cin >> totalTime;  // Chiede un nuovo input

            // Controlla se l'input è valido
            if (std::cin.fail() || totalTime <= 0) {
                std::cin.clear(); // Rimuove il flag di errore
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora il resto della riga
                std::cerr << "Input not valid." << std::endl;
            } else {
                break; // Uscire dal ciclo quando l'input è valido
            }
        }

    int i = 0;
    while (i != totalTime * 1000) {  // Simulazione dt per dt
        evolve();
        ++i;
    }

// Controllo che il valore corrente di x e y non sia negativo
    if (newX <= 0 || newY <= 0) {
        std::cerr << "Error: the number of preys and predators can not be zero or less than zero.\n";
        throw std::runtime_error(
            "Error: the number of preys and predators can not be zero or less than zero.");
    }

// Controllo che il valore corrente di x e y non sia infinito
    if (std::isinf(newX) || std::isinf(newY)) {
        std::cerr << "Error: overflow during simulation.\n";
        throw std::runtime_error("Overflow during simulation");
    }

    return data;
}

// Metodo per calcolare x relativo all'eq
double Simulation::relative_x() const {
    double x_eq = d / c;  // Punto di equilibrio per x
    return (x_eq != 0) ? (newX / x_eq) : 0;
}

// Metodo per calcolare y relativo all'eq
double Simulation::relative_y() const {
    double y_eq = a / b;  // Punto di equilibrio per y
    return (y_eq != 0) ? (newY / y_eq) : 0;
}

// Metodo per calcolare H usando i valori attuali di newX e newY
double Simulation::calculate_H() const {
    return -d * log(newX) + c * newX + b * newY - a * log(newY);
}

// Metodo per stampare i valori correnti di x, y e H
void Simulation::print(const Population& P) const {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "t =\t" << P.t << std::endl;
    std::cout << "x(" << P.t << ") =\t" << P.x
              << ",\tx_rel \t" << relative_x() << std::endl;
    std::cout << "y(" << P.t << ") =\t" << P.y
              << ",\ty_rel =\t" << relative_y() << std::endl;
    std::cout << "H(" << P.x << ", " << P.y << ") =\t" << calculate_H() << std::endl;
}



std::vector<Population> Simulation::take_data() {
    // Calcola il punto di equilibrio una volta per tutte
    const Population eq(a / c, a / b);

    if (c == 0 || b == 0) {
        std::cerr << "Error: invalid equilibrium point calculation." << std::endl;
        throw std::runtime_error("Invalid equilibrium point calculation.");
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
    const Population eq(a / c, a / b);

    // Prendi l'ultimo stato evolutivo
    const Population &last_state = data.back();

    return Population(last_state.x / eq.x, last_state.y / eq.y, last_state.H, last_state.t);
}




Simulation welcome() {
    double A, B, C, D;
    Population i_c;

    std::cout << "Welcome! This is a simulation of the Lotka-Volterra model.\nInsert the equation's parameters:\nA: ";
    std::cin >> A;

    std::cout << "B: ";
    std::cin >> B;

    std::cout << "C: ";
    std::cin >> C;

    std::cout << "D: ";
    std::cin >> D;

    std::cout << "Now insert the initial number of preys: ";
    std::cin >> i_c.x;

    std::cout << "and the initial number of predators: ";
    std::cin >> i_c.y;

    return Simulation(A, B, C, D, i_c);
}


