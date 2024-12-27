#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <stdexcept>
#include "doctest.h"
#include "simulation.hpp"
#include "simulation.cpp"


TEST_CASE("Testing Constructor") {
  Simulation simulation{1,3,5,8,{10,12}};
  Coordinates i_c{simulation.take_last()};
  CHECK(i_c.X == 6.25);
  CHECK(i_c.Y == 36);
  CHECK(i_c.t == 0);

  SUBCASE("Testing Constructor ensures t == 0") {
    Simulation simulation{1., 1., 1., 1., {10., 10., 10.}};
    Coordinates i_c{simulation.take_last()};
    CHECK(CI.X == 10.);
    CHECK(CI.Y == 10.);
    CHECK(CI.t == 0);
  }
}

   
TEST_CASE("Simulation evolve()") {
    SimulationParameters params = {0.2, 0.1, 0.3, 0.2, {10, 5, 0, 0}};
    Simulation simulation(params.A, params.B, params.C, params.D, params);
    
    double initial_x = simulation.data.front().x;
    double initial_y = simulation.data.front().y;

    sim.evolve();

    CHECK(simulation.data.size() > 1); // Check if at least one element has been added to the data vector
    CHECK(simulation.newX > 0);       // Check for positive values
    CHECK(simulation.newY > 0);       // Check for positive values
    CHECK(simulation.data.back().t > 0);  // check time has been incremented

    // Test for error handling (negative or zero populations) - needs appropriate error handling in Simulation::evolve
    // Example of how to test for this exception:
    // CHECK_THROWS_AS(sim.evolve(), std::runtime_error); 
}


TEST_CASE("Simulation run(totalTime)") {
    SimulationParameters params = {0.2, 0.1, 0.3, 0.2, {10, 5, 0, 0}};
    Simulation simulation(params.A, params.B, params.C, params.D, params);
    auto results = simulation.run(0.5);
    CHECK(results.size() > 1);

    // Add more checks if you have a specific expected outcome of the run() function,
    // possibly involving comparing results for specific timesteps against known results.

    CHECK_THROWS_AS(simulation.run(-0.5), std::invalid_argument); // Check for exception with invalid input.
}

TEST_CASE("Simulation reset()") {
    SimulationParameters params = {0.2, 0.1, 0.3, 0.2, {10, 5, 0, 0}};
    Simulation simulation(params.A, params.B, params.C, params.D, params);
    simulation.evolve(); //Do some simulation steps
    simulation.reset();
    CHECK(simulation.data.size() == 1); // check the data vector has been cleared and only contains the initial condition.
}

TEST_CASE("Simulation take_last()") {
    SimulationParameters params = {0.2, 0.1, 0.3, 0.2, {10, 5, 0, 0}};
    Simulation simulation(params.A, params.B, params.C, params.D, params);
    simulation.evolve();
    Population last = simulation.take_last();
    CHECK(last.t > 0); //Check if time is positive after evolution.
}
