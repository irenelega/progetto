#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "simulation.cpp"
#include "simulation.hpp"
#include <stdexcept>

Simulation sim(0.2, 0.1, 0.3, 0.2, {10, 5});

TEST_CASE("Simulation Constructor") {
  Population last = sim.take_last();
  CHECK(abs(last.x - 15) < 1e-6);
  CHECK(abs(last.y - 2.5) < 1e-6);
  CHECK(last.t == 0);
}

TEST_CASE("Simulation evolve()") {

  sim.evolve();
  Population last = sim.take_last();
  CHECK(abs(last.x - 14.9955) < 1e-6);
  CHECK(abs(last.y - 2.507) < 1e-6);
  CHECK(last.t == 0.001);
}

TEST_CASE("Simulation reset()") {
  sim.evolve();
  sim.reset();
  Population last = sim.take_last();
  CHECK(abs(last.x - 15) < 1e-6);
  CHECK(abs(last.y - 2.5) < 1e-6);
  CHECK(last.t == 0);
}

TEST_CASE("Simulation run()") {
  sim.reset(); // riazzero il tempo(se no partirebbe da 0.001 per la simulation
               // evolve)
  sim.run(0.003);
  Population last = sim.take_last();
  CHECK(abs(last.x - 14.9864) < 1e-4);
  CHECK(abs(last.y - 2.5210) < 1e-4);
  CHECK(last.t == 0.003);
}

TEST_CASE("Simulation take_last()") {
  sim.reset();
  sim.evolve();
  Population last = sim.take_last();
  CHECK(last.t > 0);
}
