#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/billiard.hpp"

TEST_CASE("Testing the Billiard class")
{
	CHECK_THROWS(Billiard{-1., 1., 1.});
	CHECK_THROWS(Billiard{1., -1., 1.});
	CHECK_THROWS(Billiard{1., 1., -1.});
}