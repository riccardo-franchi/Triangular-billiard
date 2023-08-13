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
		CHECK_THROWS(statistics(billiard.getParticles(), billiard.getL()));
	}

	SUBCASE("One particle")
	{
		billiard.push_back({1., 1.});
		CHECK_THROWS(statistics(billiard.getParticles(), billiard.getL()));
	}
}

TEST_CASE("Testing statistics() numerical values, alfa < 0")
{

	Billiard billiard{5., 3., 13.};

	SUBCASE("Two particles")
	{
		billiard.push_back({1.85, 0.});			// no collisions
		billiard.push_back({1., 0.0767718913}); // no collisions, y_f = 2

		CHECK(statisticsApproxEq(statistics(billiard.runSimulation(), billiard.getL()),
								 Statistics{1.925, 0.106066, 0.03838594565, 0.0542859}));
	}

	SUBCASE("Same particles")
	{
		billiard.push_back({-2., 0.2267988481}); // no collisions
		billiard.push_back({-2., 0.2267988481}); // no collisions

		CHECK(statisticsApproxEq(statistics(billiard.runSimulation(), billiard.getL()),
								 Statistics{1., 0., 0.2267988481, 0.}));
	}

	SUBCASE("Three particles")
	{
		billiard.push_back({-2.47, 0.32083});	  // no collisions
		billiard.push_back({3.35, -0.178837928}); // no collisions
		billiard.push_back({1.12534, 0.41964});	  // one collision

		CHECK(statisticsApproxEq(statistics(billiard.runSimulation(), billiard.getL()),
								 Statistics{0.3537533333, 1.90354, -0.194315976, 0.523057}));
	}

	SUBCASE("Four particles")
	{
		billiard.push_back({0., 0.});			  // no collisions
		billiard.push_back({1., 0.4357084939});	  // one collision, fin. (-1.9791249643, -0.7410071507)
		billiard.push_back({2., -0.6654199111});  // two collisions, fin. (0.5749856482, -1.2760172247)
		billiard.push_back({2.65, 0.5565549784}); // three collision, fin. (-0.1311178052, -1.4724509487)

		CHECK(statisticsApproxEq(statistics(billiard.runSimulation(), billiard.getL()),
								 Statistics{-0.383814280325, 1.10687, -0.872368831025, 0.658613}));
	}
}

TEST_CASE("Testing statistics() numerical values, alfa > 0")
{

	Billiard billiard{3., 5., 13.};

	SUBCASE("Two particles")
	{
		billiard.push_back({1., 0.0767718913}); // no collisions, y_f = 2
		billiard.push_back({0., 0.1526493284}); // no collisions, y_f = 2

		CHECK(statisticsApproxEq(statistics(billiard.runSimulation(), billiard.getL()),
								 Statistics{2., 0., 0.11471061, 0.05365345}));
	}
	SUBCASE("Same particles")
	{
		billiard.push_back({1., 0.4340593973}); // one collision
		billiard.push_back({1., 0.4340593973}); // one collision

		CHECK(statisticsApproxEq(statistics(billiard.runSimulation(), billiard.getL()),
								 Statistics{3.1464764743, 0., -0.1287607405, 0.}));
	}
}

TEST_CASE("Testing correct behaviour for particles which don't exit the billiard")
{
	Billiard billiard{5., 3., 13.};

	SUBCASE("Four particles, of which one does not escape")
	{
		billiard.push_back({-2.47, 0.32083});
		billiard.push_back({3.35, -0.178837928});
		billiard.push_back({1.12534, 0.41964});
		billiard.push_back({-4.51, 1.4521870679}); // this particle doesn't exit

		CHECK(statisticsApproxEq(statistics(billiard.runSimulation(), billiard.getL()),
								 Statistics{0.3537533333, 1.90354, -0.194315976, 0.523057}));
	}
}