#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "particle.hpp"

#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>

struct Statistics
{
	double mean{};
	double sigma{};
	double mean_err{};
	double median{};
};

struct Sums
{
	double x;
	double x2;
};

Statistics statistics(const std::vector<Particle>& particles)
{
	Sums sums{};

	int const N{particles.size()};

	if (N < 2)
	{
		throw std::runtime_error{"Not enough entries to run a statistics"};
	}

	sums = std::accumulate(particles.begin(), particles.end(), Sums{},
						   [](Sums s, double x)
						   {
							   s.x += x;
							   s.x2 += x * x;
							   return s;
						   });

	double const mean = sums.x / N;
	double const sigma = std::sqrt((sums.x2 - N * mean * mean) / (N - 1));
	double const mean_err = sigma / std::sqrt(N);

	return {mean, sigma, mean_err};
}

#endif // STATISTICS_HPP