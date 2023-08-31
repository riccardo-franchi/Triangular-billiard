#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/billiard.hpp"

bool approx_eq(const tb::Particle& particle1, const tb::Particle& particle2)
{
	constexpr double epsilon{0.0001};
	return (particle1.x == doctest::Approx(particle2.x).epsilon(epsilon) && //
			particle1.y == doctest::Approx(particle2.y).epsilon(epsilon) && //
			particle1.theta == doctest::Approx(particle2.theta).epsilon(epsilon));
}

TEST_CASE("Testing the Billiard constructor")
{
	CHECK_THROWS(tb::Billiard{-1., 1., 1.});
	CHECK_THROWS(tb::Billiard{1., -1., 1.});
	CHECK_THROWS(tb::Billiard{1., 1., -1.});
}

TEST_CASE("Testing the runSimulation() function on particle 0, alpha < 0")
{
	tb::Billiard billiard{5., 3., 13.};

	SUBCASE("Check throw for invalid angle input")
	{
		CHECK_THROWS(billiard.push_back({1.1, -13.}));
	}

	SUBCASE("Check throw if there are no particles")
	{
		CHECK_THROWS(billiard.runSimulation());
	}

	SUBCASE("No collisions, theta > 0")
	{
		billiard.push_back({-2.47, 0.32083});
		billiard.runSimulation();
		// coordinates of the last position before the collision
		CHECK(approx_eq(billiard.getParticle(0), {13., 1.85004, 0.32083}));
	}

	SUBCASE("No collisions, theta < 0")
	{
		billiard.push_back({3.35, -0.178837928});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(0), {13., 1., -0.178837928}));
	}

	SUBCASE("One collision, theta > 0")
	{
		billiard.push_back({1.12534, 0.41964});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(0), {13., -1.78878, -0.72494}));
	}

	SUBCASE("Two collisions, theta < 0")
	{
		billiard.push_back({2.43, -0.7001164822});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(0), {13, -0.923140923, -1.3107137958}));
	}

	SUBCASE("Three collisions, theta > 0")
	{
		billiard.push_back({2.65, 0.5599});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(0), {13., -0.99185, -1.4758}));
	}

	SUBCASE("One collision, the particle comes back and reaches x = 0")
	{
		billiard.push_back({-4.51, 1.4521870679});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(0), {-4.51, 1.4521870679}));
		CHECK(billiard.getEscapedParticles().size() == 0);
	}

	SUBCASE("Two collisions, alpha > 0")
	{
		billiard = {3., 5., 13.};
		billiard.push_back({1.8113483394, -1.1240743979});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(0), {13., 2.760673806, -0.5134770843}));
	}
}

TEST_CASE("Testing the runSimulation() function, alpha > 0")
{
	tb::Billiard billiard{2., 4., 10.};

	SUBCASE("No collisions, theta > 0, particle 2")
	{
		billiard.push_back({1., 0.});
		billiard.push_back({-2, 0.241214});
		billiard.push_back({-1., 0.2914567945});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(2), {10., 2., 0.2914567945}));
	}

	SUBCASE("No collisions, theta < 0, particle 1")
	{
		billiard.push_back({2., -0.78523});
		billiard.push_back({1., -0.291456794479});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(1), {10., -2., -0.291456794479}));
	}

	SUBCASE("One collision, theta > 0, particle 1")
	{
		billiard.push_back({1., -0.1548});
		billiard.push_back({0., 0.5423338184});
		billiard.runSimulation();
		CHECK(approx_eq(billiard.getParticle(1), {10., 2.2456015253, -0.1475426987}));
	}
}