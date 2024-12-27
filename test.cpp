#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <stdexcept>
#include "doctest.h"
#include "simulation.hpp" // Make sure this includes your Simulation class


// Macro for test cases (already defined in your original code)
#define TEST_CASE(name) DOCTEST_TEST_CASE(name)

TEST_CASE("Simulation Initialization") {
    SimulationParameters params = {0.2, 0.1, 0.3, 0.2, {10, 5, 0, 0}};
    Simulation sim(params.A, params.B, params.C, params.D, params);

    CHECK(sim.a == params.A);
    CHECK(sim.b == params.B);
    CHECK(sim.c == params.C);
    CHECK(sim.d == params.D);
    CHECK(sim.data.front().x == params.initial_x);
    CHECK(sim.data.front().y == params.initial_y);
    CHECK(sim.data.front().t == 0.0);


    // Test with invalid parameters (expect exceptions)
    CHECK_THROWS_AS(Simulation sim2(-0.2, 0.1, 0.3, 0.2, {10, 5, 0, 0}), std::runtime_error); //Negative parameter
    CHECK_THROWS_AS(Simulation sim3(0.2, 0.0, 0.3, 0.2, {10, 5, 0, 0}), std::runtime_error); //Zero parameter
    CHECK_THROWS_AS(Simulation sim4(0.2, 0.1, 0.0, 0.2, {10, 5, 0, 0}), std::runtime_error); //Zero parameter
}

TEST_CASE("Simulation evolve()") {
    SimulationParameters params = {0.2, 0.1, 0.3, 0.2, {10, 5, 0, 0}};
    Simulation sim(params.A, params.B, params.C, params.D, params);
    
    double initial_x = sim.data.front().x;
    double initial_y = sim.data.front().y;

    sim.evolve();

    CHECK(sim.data.size() > 1); // Check if at least one element has been added to the data vector
    CHECK(sim.newX > 0);       // Check for positive values
    CHECK(sim.newY > 0);       // Check for positive values
    CHECK(sim.data.back().t > 0);  // check time has been incremented

    // Test for error handling (negative or zero populations) - needs appropriate error handling in Simulation::evolve
    // Example of how to test for this exception:
    // CHECK_THROWS_AS(sim.evolve(), std::runtime_error); 
}


TEST_CASE("Simulation run(totalTime)") {
    SimulationParameters params = {0.2, 0.1, 0.3, 0.2, {10, 5, 0, 0}};
    Simulation sim(params.A, params.B, params.C, params.D, params);
    auto results = sim.run(0.5);
    CHECK(results.size() > 1);

    // Add more checks if you have a specific expected outcome of the run() function,
    // possibly involving comparing results for specific timesteps against known results.

    CHECK_THROWS_AS(sim.run(-0.5), std::invalid_argument); // Check for exception with invalid input.
}

TEST_CASE("Simulation reset()") {
    SimulationParameters params = {0.2, 0.1, 0.3, 0.2, {10, 5, 0, 0}};
    Simulation sim(params.A, params.B, params.C, params.D, params);
    sim.evolve(); //Do some simulation steps
    sim.reset();
    CHECK(sim.data.size() == 1); // check the data vector has been cleared and only contains the initial condition.
}

TEST_CASE("Simulation take_last()") {
    SimulationParameters params = {0.2, 0.1, 0.3, 0.2, {10, 5, 0, 0}};
    Simulation sim(params.A, params.B, params.C, params.D, params);
    sim.evolve();
    Population last = sim.take_last();
    CHECK(last.t > 0); //Check if time is positive after evolution.
}
