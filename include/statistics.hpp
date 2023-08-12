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
	double skewness_y{};
	double skewness_th{};
	double kurtosis_y{};
	double kurtosis_th{};
};

struct Sums
{
	double yf;
	double yf2;
	double th;
	double th2;
};

struct Gaps
{
	double y3;
	double th3;
	double y4;
	double th4;
};

Statistics statistics(const std::vector<Particle>& particles)
{
	Sums sums{};

	int const N{static_cast<int>(particles.size())};

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
	double const sigma_y{std::sqrt((sums.yf2 - N * mean_y * mean_y) / (N - 1))};	// why not mean sigma?
	double const mean_th{sums.th / N};
	double const sigma_th{std::sqrt((sums.th2 - N * mean_th * mean_th) / (N - 1))}; // idem
	// double const mean_err = sigma / std::sqrt(N);

	Gaps gaps{};
	for (auto i{particles.begin()}; i != particles.end(); i++)
	{
		Particle p{*i};
		gaps.y3 += (p.y - mean_y) * (p.y - mean_y) * (p.y - mean_y);
		gaps.y4 += (p.y - mean_y) * (p.y - mean_y) * (p.y - mean_y) * (p.y - mean_y);
		gaps.th3 += (p.theta - mean_th) * (p.theta - mean_th) * (p.theta - mean_th);
		gaps.th4 += (p.theta - mean_th) * (p.theta - mean_th) * (p.theta - mean_th) * (p.theta - mean_th);
	}

	/*
	gaps = std::accumulate(particles.begin(), particles.end(), Gaps{0., 0., 0., 0.},
							   [](Gaps g, Particle p)
							   {
								   g.y2 += (p.y - mean_y)*(p.y - mean_y);
								   g.y2 += (p.y - mean_y)*(p.y - mean_y)*(p.y - mean_y);
								   g.th2 += (p.theta - mean_th)*(p.theta - mean_th);
								   g.th3 += (p.theta - mean_th)*(p.theta - mean_th)*(p.theta - mean_th);
								   return g;
							   });
							   */

	double const skewness_y{gaps.y3 / (N * sigma_y * sigma_y * sigma_y)};
	double const skewness_th{gaps.th3 / (N * sigma_th * sigma_th * sigma_th)};
	double const kurtosis_y{gaps.y4 / (N * sigma_y * sigma_y * sigma_y * sigma_y)};
	double const kurtosis_th{gaps.th4 / (N * sigma_th * sigma_th * sigma_th * sigma_th)};

	return {mean_y, sigma_y, mean_th, sigma_th, skewness_y, skewness_th, kurtosis_y, kurtosis_th};
}

#endif // STATISTICS_HPP