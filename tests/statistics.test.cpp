#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/billiard.hpp"
#include "../include/statistics.hpp"

bool statisticsApproxEq(const tb::Results& stat1, const tb::Results& stat2)
{
	constexpr double epsilon{0.0001};
	return (stat1.y.mean == doctest::Approx(stat2.y.mean).epsilon(epsilon) &&
			stat1.y.sigma == doctest::Approx(stat2.y.sigma).epsilon(epsilon) &&
			stat1.theta.mean == doctest::Approx(stat2.theta.mean).epsilon(epsilon) &&
			stat1.theta.sigma == doctest::Approx(stat2.theta.sigma).epsilon(epsilon));
}

bool statisticsApproxEq2(const tb::Results& stat1, const tb::Results& stat2)
{
	constexpr double epsilon{0.0001};
	return (stat1.y.mean == doctest::Approx(stat2.y.mean).epsilon(epsilon) &&
			stat1.y.sigma == doctest::Approx(stat2.y.sigma).epsilon(epsilon) &&
			stat1.y.skewness == doctest::Approx(stat2.y.skewness).epsilon(epsilon) &&
			stat1.y.kurtosis == doctest::Approx(stat2.y.kurtosis).epsilon(epsilon) &&
			stat1.theta.mean == doctest::Approx(stat2.theta.mean).epsilon(epsilon) &&
			stat1.theta.sigma == doctest::Approx(stat2.theta.sigma).epsilon(epsilon) &&
			stat1.theta.skewness == doctest::Approx(stat2.theta.skewness).epsilon(epsilon) &&
			stat1.theta.kurtosis == doctest::Approx(stat2.theta.kurtosis).epsilon(epsilon));
}

TEST_CASE("Testing statistics() throws")
{
	tb::Billiard billiard{5., 3., 13.};

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
		CHECK_THROWS(statistics(billiard.getEscapedParticles()));
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
		CHECK_THROWS(statistics(billiard.getEscapedParticles()));
	}
}

TEST_CASE("Testing statistics() numerical values, alpha < 0")
{
	tb::Billiard billiard{5., 3., 13.};

	SUBCASE("Two particles")
	{
		billiard.push_back({1.85, 0.});			// no collisions
		billiard.push_back({1., 0.0767718913}); // no collisions
		billiard.runSimulation();
		CHECK(statisticsApproxEq(statistics(billiard.getParticles()),
								 tb::Results{{1.925, 0.106066}, {0.038385946, 0.0542859}}));
	}

	SUBCASE("Same particles")
	{
		billiard.push_back({-2., 0.2267988481}); // no collisions
		billiard.push_back({-2., 0.2267988481}); // no collisions
		billiard.runSimulation();
		CHECK(statisticsApproxEq(statistics(billiard.getParticles()), tb::Results{{1., 0.}, {0.2267988481, 0.}}));
	}

	SUBCASE("Three particles")
	{
		billiard.push_back({-2.47, 0.32083});	  // no collisions
		billiard.push_back({3.35, -0.178837928}); // no collisions
		billiard.push_back({1.12534, 0.41964});	  // one collision
		billiard.runSimulation();
		CHECK(statisticsApproxEq(statistics(billiard.getParticles()),
								 tb::Results{{0.3537533333, 1.90354}, {-0.194315976, 0.523057}}));
	}
}

TEST_CASE("Testing statistics() numerical values, alpha > 0")
{

	tb::Billiard billiard{3., 5., 13.};

	SUBCASE("Same particles")
	{
		billiard.push_back({2., 0.4500214252}); // one collision
		billiard.push_back({2., 0.4500214252}); // one collisions
		billiard.runSimulation();
		CHECK(statisticsApproxEq(statistics(billiard.getParticles()),
								 tb::Results{{2.0153084196, 0.}, {0. - 0.1447227684, 0.}}));
	}

	SUBCASE("Two particles")
	{
		billiard.push_back({1., 0.0767718913}); // no collisions
		billiard.push_back({0., 0.1526493284}); // no collisions
		billiard.runSimulation();
		CHECK(statisticsApproxEq(statistics(billiard.getParticles()), tb::Results{{2., 0.}, {0.114711, 0.053653}}));
	}
}

TEST_CASE("Testing statistics() numerical values, alpha > 0, different billiard")
{
	tb::Billiard billiard{3., 4., 12.};

	SUBCASE("Same particles")
	{
		billiard.push_back({-2., 0.3217505544}); // no collisions
		billiard.push_back({-2., 0.3217505544}); // no collisions
		billiard.runSimulation();
		CHECK(statisticsApproxEq(statistics(billiard.getParticles()), tb::Results{{2., 0.}, {0.3217505544, 0.}}));
	}

	SUBCASE("Two particles")
	{
		billiard.push_back({-2., 0.7448900202}); // one collision
		billiard.push_back({-1., 0.6462755507}); // one collision
		billiard.runSimulation();
		CHECK(statisticsApproxEq(statistics(billiard.getParticles()),
								 tb::Results{{-0.047380676, 0.566122567}, {-0.529300322, 0.06973096}}));
	}

	SUBCASE("Three particles")
	{
		billiard.push_back({2., 0.0831412319}); // no collision
		billiard.push_back({2., 0.2477287421}); // one collision
		billiard.push_back({3., 0.});			// no collisions
		billiard.runSimulation();
		CHECK(statisticsApproxEq(statistics(billiard.getParticles()),
								 tb::Results{{2.997724687, 0.003940957}, {0.000564985, 0.08229521}}));
	}

	SUBCASE("Four particles")
	{
		billiard.push_back({0.49, 0.});			 // no collision
		billiard.push_back({2., 0.2460005466});	 // one collision
		billiard.push_back({-2., 0.2449786631}); // no collisions
		billiard.push_back({1., 0.3966404392});	 // one collision
		billiard.runSimulation();
		CHECK(statisticsApproxEq(statistics(billiard.getParticles()),
								 tb::Results{{1.646215724, 1.127653618}, {-0.016274349, 0.198641131}}));
	}
}

TEST_CASE("Testing statistics() numerical values, alpha < 0, w/ skewness and kurtosis")
{
	tb::Billiard billiard{5., 3., 13.};

	SUBCASE("Two particles")
	{
		billiard.push_back({1., 0.0767718913});	 // no collisions
		billiard.push_back({3., -0.7283865634}); // two collisions
		billiard.runSimulation();
		CHECK(statisticsApproxEq(
			statistics(billiard.getParticles()),
			tb::Results{{0.09244634, 2.697688257, 0., 0.25}, {-0.631105993, 1.001090504, 0., 0.25}}));
	}

	SUBCASE("Null particles")
	{
		billiard.push_back({0., 0.}); // no collisions
		billiard.push_back({0., 0.}); // no collisions
		billiard.push_back({0., 0.}); // no collisions
		billiard.push_back({0., 0.}); // no collisions
		billiard.runSimulation();
		CHECK(statisticsApproxEq(statistics(billiard.getParticles()), tb::Results{{0., 0., 0., 0.}, {0., 0., 0., 0.}}));
	}

	SUBCASE("Same particles")
	{
		billiard.push_back({2., -0.6506834171}); // two collisions
		billiard.push_back({2., -0.6506834171}); // two collisions
		billiard.push_back({2., -0.6506834171}); // two collisions
		billiard.push_back({2., -0.6506834171}); // two collisions
		billiard.push_back({2., -0.6506834171}); // two collisions
		billiard.push_back({2., -0.6506834171}); // two collisions
		billiard.runSimulation();
		CHECK(statisticsApproxEq(statistics(billiard.getParticles()),
								 tb::Results{{1.570888912, 0., 0., 0.}, {-1.261280731, 0., 0., 0.}}));
	}

	SUBCASE("Three particles")
	{
		billiard.push_back({-2.47, 0.3208271936}); // no collisions
		billiard.push_back({-2., 0.2984989316});   // no collisions
		billiard.push_back({4., 0.001002488});	   // one collision
		billiard.runSimulation();
		CHECK(statisticsApproxEq(statistics(billiard.getParticles()),
								 tb::Results{{1.929171752, 0.075347266, -0.109376168, 0.666666667},
											 {0.104342596, 0.355803148, -0.38319519, 0.666666667}}));
	}

	SUBCASE("Four particles w/ skewness and kurtosis")
	{
		billiard.push_back({0., 0.});			  // no collisions
		billiard.push_back({1., 0.4357084939});	  // one collision
		billiard.push_back({2., -0.6654199111});  // two collisions
		billiard.push_back({2.65, 0.5565549784}); // three collision
		billiard.runSimulation();
		CHECK(statisticsApproxEq2(statistics(billiard.getParticles()),
								  tb::Results{{-0.383814280325, 1.10687, -0.57259892459, 1.2238334345},
											  {-0.872368831025, 0.658613, 0.33630075, 0.977477404}}));
	}
}