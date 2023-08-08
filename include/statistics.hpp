#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "particle.hpp"

#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>

struct Statistics
{
	double mean_y{};
	double sigma_y{};
	double mean_theta{};
	double sigma_theta{};
};

struct Sums
{
	double yf;
	double yf2;
	double th;
	double th2;
};

Statistics statistics(const std::vector<Particle>& particles)
{
	Sums sums{};

	int const N{particles.size()};

	if (N < 2)
	{
		throw std::runtime_error{"Not enough entries to run a statistics"};
	}

	sums = std::accumulate(particles.begin(), particles.end(), Sums{0., 0., 0., 0.},
						   [](Sums s, Particle p)
						   {
							   s.yf += p.y;
							   s.yf2 += p.y * p.y;
							   s.th += p.theta;
							   s.th2 += p.theta * p.theta;
							   return s;
						   });

	double const mean_y{sums.yf / N};
	double const sigma_y{std::sqrt((sums.yf2 - N * mean_y * mean_y) / (N - 1))}; // why not mean sigma?
	double const mean_th{sums.th / N};
	double const sigma_th{std::sqrt((sums.th2 - N * mean_th * mean_th) / (N - 1))}; // idem
	// double const mean_err = sigma / std::sqrt(N);

	return {mean_y, sigma_y, mean_th, sigma_th};
}

#endif // STATISTICS_HPP