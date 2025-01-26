#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "simulation.hpp"
#include <stdexcept>
using namespace LotkaVolterra;

TEST_CASE("Simulation evolve() negative populations") {
  SUBCASE("Negative populations") {
    Simulation sim(10000, 0.1, 0.1, 0.1, {1000000, 100});
    sim.evolve();
    sim.evolve();
    CHECK_THROWS_AS(sim.evolve(), std::runtime_error);
  }

  SUBCASE("Overflow populations") {
    Simulation sim(0.2, 0.1, 0.3, 0.2, {100, 1e308});
    CHECK_THROWS_AS(sim.evolve(), std::runtime_error);
  }
}

TEST_CASE("Simulation Constructor") {
  Simulation sim(0.2, 0.1, 0.3, 0.2, {10, 5});
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
  Simulation sim(0.2, 0.1, 0.3, 0.2, {10, 5});
  sim.evolve();
  Population last = sim.take_last();
  CHECK(abs(last.x - 14.9955) < 1e-6);
  CHECK(abs(last.y - 2.507) < 1e-6);
  CHECK(last.t == 0.001);
}

TEST_CASE("Simulation reset()") {
  Simulation sim(0.2, 0.1, 0.3, 0.2, {10, 5});
  sim.evolve();
  sim.reset();
  Population last = sim.take_last();
  CHECK(abs(last.x - 15) < 1e-6);
  CHECK(abs(last.y - 2.5) < 1e-6);
  CHECK(last.t == 0);
}

TEST_CASE("Simulation run()") {
  Simulation sim(0.2, 0.1, 0.3, 0.2, {10, 5});
  sim.reset();
  sim.run(0.003);
  Population last = sim.take_last();
  CHECK(abs(last.x - 14.9864) < 1e-4);
  CHECK(abs(last.y - 2.5210) < 1e-4);
  CHECK(last.t == 0.003);
}

TEST_CASE("Simulation take_last()") {
  Simulation sim(0.2, 0.1, 0.3, 0.2, {10, 5});
  sim.reset();
  sim.evolve();
  Population last = sim.take_last();
  CHECK(last.t > 0);
}

TEST_CASE("Simulation calculate_H()") {
  Simulation sim(0.2, 0.1, 0.3, 0.2, {10, 5});
  double H = sim.calculate_H();
  CHECK(abs(H - 2.7176) < 1e-4);
}

TEST_CASE("Simulation relative_x()") {
  Simulation sim(0.2, 0.1, 0.3, 0.2, {10, 5});
  sim.reset();
  sim.evolve();
  double x_rel = sim.relative_x();
  CHECK(abs(x_rel - 14.9955) < 1e-6);
}

TEST_CASE("Simulation relative_y()") {
  Simulation sim(0.2, 0.1, 0.3, 0.2, {10, 5});
  sim.reset();
  sim.evolve();
  double y_rel = sim.relative_y();
  CHECK(abs(y_rel - 2.507) < 1e-6);
}

TEST_CASE("Simulation normalization in print_data()") {
  Population eq{10, 5};
  std::vector<Population> data = {Population{20, 10}, Population{30, 15},
                                  Population{40, 20}};

  // Vettore per i dati normalizzati
  std::vector<Population> norm_data(data.size());

  std::transform(data.begin(), data.end(), norm_data.begin(),
                 [&eq](const Population &P) {
                   return Population(P.x / eq.x, P.y / eq.y, P.t);
                 });

  CHECK(abs(norm_data[0].x - 2.0) < 1e-6);
  CHECK(abs(norm_data[0].y - 2.0) < 1e-6);

  CHECK(abs(norm_data[1].x - 3.0) < 1e-6);
  CHECK(abs(norm_data[1].y - 3.0) < 1e-6);

  CHECK(abs(norm_data[2].x - 4.0) < 1e-6);
  CHECK(abs(norm_data[2].y - 4.0) < 1e-6);
}
