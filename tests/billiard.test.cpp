#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/billiard.hpp"
#include "../include/particle.hpp"

TEST_CASE("Testing the Billiard class")
{
	// CHECK_THROWS(Billiard{-1., 1., 1.});
	// CHECK_THROWS(Billiard{1., -1., 1.});
	CHECK_THROWS(Billiard{1., 1., -1.});
}

TEST_CASE("Testing the collide function")
{
	Particle particle{10., 0.};
	Billiard billiard{4., 6., 20.};
	CHECK(collide(particle, billiard) == false);
}