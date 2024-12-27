#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <stdexcept>
#include "doctest.h"
#include "simulation.hpp"
#include "simulation.cpp"

Simulation sim(0.2, 0.1, 0.3, 0.2, {10, 5});

TEST_CASE("Simulation Constructor") {
    // Test with valid parameters
    
    
    Population last = sim.take_last();

    // Aggiungi debug per stampare i valori
    std::cout << "last.x: " << last.x << "\n";
    std::cout << "last.y: " << last.y << "\n";
    std::cout << "last.t: " << last.t << "\n";

    // Verifica i valori
    CHECK(abs(last.x - 15) < 1e-6);
    CHECK(abs(last.y - 2.5) < 1e-6);
    CHECK(last.t == 0);

    /*
    //Test with invalid parameters (expect exceptions)
    CHECK_THROWS_AS(Simulation sim2(-0.2, 0.1, 0.3, 0.2, {10, 5}), std::runtime_error);
    CHECK_THROWS_AS(Simulation sim3(0.2, 0.0, 0.3, 0.2, {10, 5}), std::runtime_error);
    CHECK_THROWS_AS(Simulation sim4(0.2, 0.1, 0.0, 0.2, {10, 5}), std::runtime_error);
    CHECK_THROWS_AS(Simulation sim5(0.2, 0.1, 0.3, 0.2, {-10, 5}), std::runtime_error);
    CHECK_THROWS_AS(Simulation sim6(0.2, 0.1, 0.3, 0.2, {10, -5}), std::runtime_error);
    CHECK_THROWS_AS(Simulation sim7(0.2, 0.1, 0.3, 0.2, {0, 5}), std::runtime_error);
    CHECK_THROWS_AS(Simulation sim8(0.2, 0.1, 0.3, 0.2, {10, 0}), std::runtime_error);
    CHECK_THROWS_AS(Simulation sim9(0, 0.1, 0.3, 0.2, {10, 5}), std::runtime_error);
    */
    }



TEST_CASE("Simulation evolve()") {
    
    sim.evolve();
    Population last = sim.take_last();
    std::cout << "last.x: " << last.x << "\n";
    std::cout << "last.y: " << last.y << "\n";
    std::cout << "last.t: " << last.t << "\n";
    CHECK(abs(last.x - 14.9955) < 1e-6);
    CHECK(abs(last.y - 2.507) < 1e-6);
    CHECK(last.t == 0.001);
}

TEST_CASE("Simulation reset()") {
    sim.evolve();
    sim.reset();
    Population last = sim.take_last();
    std::cout << "last.x: " << last.x << "\n";
    std::cout << "last.y: " << last.y << "\n";
    std::cout << "last.t: " << last.t << "\n";
    CHECK(abs(last.x - 15) < 1e-6);
    CHECK(abs(last.y - 2.5) < 1e-6);
    CHECK(last.t == 0);
}

TEST_CASE("Simulation run()") {
    sim.reset(); //riazzero il tempo(se no partirebbe da 0.001 per la simulation evolve)
    sim.run(0.003);
    Population last = sim.take_last();
    std::cout << "last.x: " << last.x << "\n";
    std::cout << "last.y: " << last.y << "\n";
    std::cout << "last.t: " << last.t << "\n";
    CHECK(abs(last.x - 14.9864) < 1e-4);
    CHECK(abs(last.y - 2.52105) < 1e-5);
    CHECK(last.t == 0.003);
}

TEST_CASE("Simulation take_last()") {
    sim.reset();
    sim.evolve();
    Population last = sim.take_last();
    std::cout << "last.x: " << last.x << "\n";
    std::cout << "last.y: " << last.y << "\n";
    std::cout << "last.t: " << last.t << "\n";
    CHECK(last.t > 0);
}
