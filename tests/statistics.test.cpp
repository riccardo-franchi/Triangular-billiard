#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/billiard.hpp"
#include "../include/statistics.hpp"

bool statisticsApproxEq(const Statistics& stat1, const Statistics& stat2)
{
	const double epsilon{0.0001};
	return (stat1.mean == doctest::Approx(stat2.mean).epsilon(epsilon) &&
			stat1.mean_err == doctest::Approx(stat2.mean_err).epsilon(epsilon) &&
			stat1.median == doctest::Approx(stat2.median).epsilon(epsilon) &&
			stat1.sigma == doctest::Approx(stat2.sigma).epsilon(epsilon));
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
		CHECK_THROWS(billiard.getParticles());
	}
}

/* TEST_CASE("Testing statistics() numerical values")
{

	Billiard billiard{5., 3., 13.};

	SUBCASE("Three particles")
	{
		billiard.push_back({-2.47, 0.32083});	  // no collisions
		billiard.push_back({3.35, -0.178837928}); // no collisions
		billiard.push_back({1.12534, 0.41964});	  // one collision
		billiard.runSimulation();

		CHECK(statisticsApproxEq(statistics(billiard.getParticles())));
	}
} */