#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/billiard.hpp"

bool approx_eq(const Particle& particle1, const Particle& particle2)
{
	return (particle1.x == doctest::Approx(particle2.x) && //
			particle1.y == doctest::Approx(particle2.y) && //
			particle1.theta == doctest::Approx(particle2.theta));
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

	SUBCASE("No collisions")
	{
		billiard.setParticle({-2.47, 0.32083});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(), {13., 1.85, 0.32083}));
	}

	SUBCASE("One collision, theta > 0")
	{
		billiard.setParticle({1.12534, 0.41964});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(), {13., -1.78878, -0.72494}));
	}

	SUBCASE("Three collisions, theta > 0")
	{
		billiard.setParticle({2.63, 0.5613});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(), {13., -1.18987, -1.4772}));
	}
}