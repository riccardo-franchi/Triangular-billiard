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

TEST_CASE("Three collisions, theta>0")
{
	Billiard billiard{5., 3., 13.};
	billiard.setParticle({2.6, 0.561298});

	SUBCASE("Testing the runSimulation() function")
	{
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(), {13., -1.19, -1.477194}));
	}
}