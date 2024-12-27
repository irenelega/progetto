#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "simulation.cpp"
#include "simulation.hpp"
#include <stdexcept>

TEST_CASE("Simulation evolve() negative populations and overflow") {

  SUBCASE("Negative populations") {
    Simulation sim(0.2, 0.1, 0.3, 0.2, {0, 5});
    CHECK_THROWS_AS(sim.evolve(), std::runtime_error);
  }

  SUBCASE("Overflow populations") {
    Simulation sim(0.2, 0.1, 0.3, 0.2, {1e10, 1e10});
    CHECK_THROWS_AS(sim.evolve(), std::runtime_error);
  }
}

Simulation sim(0.2, 0.1, 0.3, 0.2, {10, 5});

TEST_CASE("Simulation Constructor") {
  Population last = sim.take_last();
  CHECK(abs(last.x - 15) < 1e-6);
  CHECK(abs(last.y - 2.5) < 1e-6);
  CHECK(last.t == 0);
}

TEST_CASE("Testing operator /") {
  Population P{10, 10};
  Population eq{1, 2};
  Population rel = P / eq;
  CHECK(rel.x == 10);
  CHECK(rel.y == 5);
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

TEST_CASE("Simulation calculate_H()") {
  double H = sim.calculate_H();
  CHECK(abs(H - 2.7176) < 1e-4);
}

TEST_CASE("Simulation relative_x()") {
  double x_rel = sim.relative_x();
  CHECK(abs(x_rel - 14.9955) < 1e-6);
}

TEST_CASE("Simulation relative_y()") {
  double y_rel = sim.relative_y();
  CHECK(abs(y_rel - 2.507) < 1e-6);
}
