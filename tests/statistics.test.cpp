#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/billiard.hpp"
#include "../include/statistics.hpp"

bool statisticsApproxEq(const bs::Statistics::Statistics::Results& stat1,
						const bs::Statistics::Statistics::Results& stat2)
{
	const double epsilon{0.0001};
	return (stat1.y.mean == doctest::Approx(stat2.y.mean).epsilon(epsilon) &&
			stat1.y.sigma == doctest::Approx(stat2.y.sigma).epsilon(epsilon) &&
			stat1.theta.mean == doctest::Approx(stat2.theta.mean).epsilon(epsilon) &&
			stat1.theta.sigma == doctest::Approx(stat2.theta.sigma).epsilon(epsilon));
}

/*bool statisticsApproxEq2(const Statistics& stat1, const Statistics& stat2)
{
	const double epsilon{0.0001};
	return (stat1.mean_y == doctest::Approx(stat2.mean_y).epsilon(epsilon) &&
			stat1.sigma_y == doctest::Approx(stat2.sigma_y).epsilon(epsilon) &&
			stat1.mean_theta == doctest::Approx(stat2.mean_theta).epsilon(epsilon) &&
			stat1.sigma_theta == doctest::Approx(stat2.sigma_theta).epsilon(epsilon) &&
			stat1.skewness_y == doctest::Approx(stat2.skewness_y).epsilon(epsilon) &&
			stat1.skewness_th == doctest::Approx(stat2.skewness_th).epsilon(epsilon) &&
			stat1.kurtosis_y == doctest::Approx(stat2.kurtosis_y).epsilon(epsilon) &&
			stat1.kurtosis_th == doctest::Approx(stat2.kurtosis_th).epsilon(epsilon));
}*/

TEST_CASE("Testing statistics() throws")
{
	bs::Billiard billiard{5., 3., 13.};
	bs::Statistics statistics{billiard.getL()};

	SUBCASE("No particles")
	{
		CHECK_THROWS(statistics(billiard.getParticles()));
	}

	SUBCASE("One particle")
	{
		billiard.push_back({1., 1.});
		CHECK_THROWS(statistics(billiard.getParticles()));
	}

	SUBCASE("Two particles, one does not escape the billiard")
	{
		billiard.push_back({2., 0.7});
		billiard.push_back({-4.51, 1.4521870679}); // does not escape
		billiard.runSimulation();
		CHECK_THROWS(statistics(billiard.getParticles()));
	}

	SUBCASE("Ten particles, none of them escapes the billiard")
	{
		billiard.push_back({-2., 1.3173361955});
		billiard.push_back({-4., 1.3423777985});
		billiard.push_back({0., 1.3553648436});
		billiard.push_back({-0.15, 1.3462769726});
		billiard.push_back({-2.35, 1.3963817285});
		billiard.push_back({3., 1.3055483599});
		billiard.push_back({0., 1.4897168558});
		billiard.push_back({-4.85, 1.3515529184});
		billiard.push_back({-3., 1.3726015944});
		billiard.push_back({-1, 1.4053271879});
		billiard.runSimulation();
		CHECK_THROWS(statistics(billiard.getParticles()));
	}
}

TEST_CASE("Testing statistics() numerical values, alfa < 0")
{
	bs::Billiard billiard{5., 3., 13.};
	bs::Statistics statistics{billiard.getL()};

	SUBCASE("Two particles")
	{
		billiard.push_back({1.85, 0.});			// no collisions
		billiard.push_back({1., 0.0767718913}); // no collisions, y_f = 2

		CHECK(statisticsApproxEq(statistics(billiard.runSimulation()),
								 bs::Statistics::Results{{1.925, 0.106066}, {0.03838594565, 0.0542859}}));
	}

	SUBCASE("Same particles")
	{
		billiard.push_back({-2., 0.2267988481}); // no collisions
		billiard.push_back({-2., 0.2267988481}); // no collisions

		CHECK(statisticsApproxEq(statistics(billiard.runSimulation()),
								 bs::Statistics::Results{{1., 0.}, {0.2267988481, 0.}}));
	}

	SUBCASE("Three particles")
	{
		billiard.push_back({-2.47, 0.32083});	  // no collisions
		billiard.push_back({3.35, -0.178837928}); // no collisions
		billiard.push_back({1.12534, 0.41964});	  // one collision

		CHECK(statisticsApproxEq(statistics(billiard.runSimulation()),
								 bs::Statistics::Results{{0.3537533333, 1.90354}, {-0.194315976, 0.523057}}));
	}

	SUBCASE("Four particles w/ skewness and kurtosis")
	{
		billiard.push_back({0., 0.});			  // no collisions
		billiard.push_back({1., 0.4357084939});	  // one collision, fin. (-1.9791249643, -0.7410071507)
		billiard.push_back({2., -0.6654199111});  // two collisions, fin. (0.5749856482, -1.2760172247)
		billiard.push_back({2.65, 0.5565549784}); // three collision, fin. (-0.1311178052, -1.4724509487)

		CHECK(statisticsApproxEq(statistics(billiard.runSimulation()),
								 bs::Statistics::Results{{-0.383814280325, 1.10687}, {-0.872368831025, 0.658613}}));
	}
}

TEST_CASE("Testing statistics() numerical values, alfa > 0")
{
	bs::Billiard billiard{3., 4., 12.};
	bs::Statistics statistics{billiard.getL()};

	SUBCASE("Same particles")
	{
		billiard.push_back({-2., 0.3217505544}); // no collisions
		billiard.push_back({-2., 0.3217505544}); // no collisions

		CHECK(statisticsApproxEq(statistics(billiard.runSimulation()),
								 bs::Statistics::Results{{2., 0.}, {0.3217505544, 0.}}));
	}
}