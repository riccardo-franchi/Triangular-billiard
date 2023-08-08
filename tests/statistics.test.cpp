#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/billiard.hpp"
#include "../include/statistics.hpp"

bool statisticsApproxEq(const Statistics& stat1, const Statistics& stat2)
{
	const double epsilon{0.0001};
	return (stat1.mean_y == doctest::Approx(stat2.mean_y).epsilon(epsilon) &&
			stat1.sigma_y == doctest::Approx(stat2.sigma_y).epsilon(epsilon) &&
			stat1.mean_theta == doctest::Approx(stat2.mean_theta).epsilon(epsilon) &&
			stat1.sigma_theta == doctest::Approx(stat2.sigma_theta).epsilon(epsilon));
}

TEST_CASE("Testing statistics() throws")
{
	Billiard billiard{5., 3., 13.};

	SUBCASE("No particles")
	{
		CHECK_THROWS(statistics(billiard.getParticles()));
	}

	SUBCASE("One particle")
	{
		billiard.push_back({1., 1.});
		CHECK_THROWS(statistics(billiard.getParticles()));
	}
}

TEST_CASE("Testing statistics() numerical values")
{

	Billiard billiard{5., 3., 13.};

	SUBCASE("Three particles")
	{
		billiard.push_back({-2.47, 0.32083});	  // no collisions
		billiard.push_back({3.35, -0.178837928}); // no collisions
		billiard.push_back({1.12534, 0.41964});	  // one collision
		billiard.runSimulation();

		CHECK(statisticsApproxEq(statistics(billiard.getParticles()),
								 Statistics{0.3537533333, 1.90354, -0.194315976, 0.523057}));
	}
}