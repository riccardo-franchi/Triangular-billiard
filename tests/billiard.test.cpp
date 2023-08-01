#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/billiard.hpp"

TEST_CASE("Testing the Billiard class")
{
	SUBCASE("Negative r1 throws")
	{
		CHECK_THROWS(Billiard{-1., 1., 1.});
	}
	SUBCASE("Negative r2 throws")
	{
		CHECK_THROWS(Billiard{1., -1., 1.});
	}
	SUBCASE("Negative l throws")
	{
		CHECK_THROWS(Billiard{1., 1., -1.});
	}
}