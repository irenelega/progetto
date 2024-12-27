#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <stdexcept>
#include "doctest.h"
#include "simulation.hpp"

#define TEST_CASE(name) DOCTEST_TEST_CASE(name)

TEST_CASE("Simulation Constructor") {
    // Test with valid parameters
    Simulation sim1(0.2, 0.1, 0.3, 0.2, 10, 5);
    CHECK(sim1.a == 0.2);
    CHECK(sim1.b == 0.1);
    CHECK(sim1.c == 0.3);
    CHECK(sim1.d == 0.2);
    CHECK(sim1.data.front().x == 10);
    CHECK(sim1.data.front().y == 5);
    CHECK(sim1.data.front().t == 0);

    // Test with invalid parameters (expect exceptions)
    CHECK_THROWS_AS(Simulation sim2(-0.2, 0.1, 0.3, 0.2, 10, 5), std::runtime_error);
    CHECK_THROWS_AS(Simulation sim3(0.2, 0.0, 0.3, 0.2, 10, 5), std::runtime_error);
    CHECK_THROWS_AS(Simulation sim4(0.2, 0.1, 0.0, 0.2, 10, 5), std::runtime_error);
    CHECK_THROWS_AS(Simulation sim5(0.2, 0.1, 0.3, 0.2, -10, 5), std::runtime_error);
    CHECK_THROWS_AS(Simulation sim6(0.2, 0.1, 0.3, 0.2, 10, -5), std::runtime_error);
    CHECK_THROWS_AS(Simulation sim7(0.2, 0.1, 0.3, 0.2, 0, 5), std::runtime_error);
    CHECK_THROWS_AS(Simulation sim8(0.2, 0.1, 0.3, 0.2, 10, 0), std::runtime_error);
    CHECK_THROWS_AS(Simulation sim9(0, 0.1, 0.3, 0.2, 10, 5), std::runtime_error);
}

TEST_CASE("Simulation evolve()") {
    Simulation sim(0.2, 0.1, 0.3, 0.2, 10, 5);
    sim.evolve();
    CHECK(sim.data.size() == 2);
    CHECK(sim.newX > 0);
    CHECK(sim.newY > 0);
    CHECK(sim.t == Approx(0.001));
}

TEST_CASE("Simulation run()") {
    Simulation sim(0.2, 0.1, 0.3, 0.2, 10, 5);
    auto results = sim.run(0.1);
    CHECK(results.size() > 1);
}

TEST_CASE("Simulation reset()") {
    Simulation sim(0.2, 0.1, 0.3, 0.2, 10, 5);
    sim.evolve();
    sim.reset();
    CHECK(sim.data.size() == 1);
}

TEST_CASE("Simulation take_last()") {
    Simulation sim(0.2, 0.1, 0.3, 0.2, 10, 5);
    sim.evolve();
    Population last = sim.take_last();
    CHECK(last.t > 0);
}
