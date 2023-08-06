#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/billiard.hpp"

bool approx_eq(const Particle& particle1, const Particle& particle2)
{
	return (particle1.x == doctest::Approx(particle2.x).epsilon(0.0001) && //
			particle1.y == doctest::Approx(particle2.y).epsilon(0.0001) && //
			particle1.theta == doctest::Approx(particle2.theta).epsilon(0.0001));
}

TEST_CASE("Testing the Billiard constructor")
{
	CHECK_THROWS(Billiard{-1., 1., 1.});
	CHECK_THROWS(Billiard{1., -1., 1.});
	CHECK_THROWS(Billiard{1., 1., -1.});
}

TEST_CASE("Testing the runSimulation() function")
{
	Billiard billiard{5., 3., 13.};

	SUBCASE("Check throw for invalid angle input")
	{
		CHECK_THROWS(billiard.setParticle({1.1, -13}));
	}

	SUBCASE("No collisions")
	{
		billiard.setParticle({-2.47, 0.32083});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(), {13., 1.85004, 0.32083}));
	}

	SUBCASE("One collision, theta > 0")
	{
		billiard.setParticle({1.12534, 0.41964});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(), {13., -1.78878, -0.72494}));
	}

	SUBCASE("Three collisions, theta > 0")
	{
		billiard.setParticle({2.65, 0.5599});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(), {13., -0.99185, -1.4758}));
	}

	SUBCASE("No collisions, theta < 0")
	{
		billiard.setParticle({3.35, -0.178837928});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(), {13., 1., -0.178837928}));
	}

	SUBCASE("Two collisions, theta < 0")
	{
		billiard.setParticle({2.43, -0.7001164822});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(), {13, -0.923140923, -1.3107137958}));
	}

	SUBCASE("One collision, the particle comes back and reaches x = 0")
	{
		billiard.setParticle({-4.51, 1.4521870679});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(), {1.1128901734, 4.8287861272, -1.7574857247}));
	}

	billiard = {3, 5, 13};

	SUBCASE("Two collisions, alpha > 0")
	{
		billiard.setParticle({1.8113483394, -1.1240743979});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(), {13, 2.760673806, -0.5134770843}));
	}
}