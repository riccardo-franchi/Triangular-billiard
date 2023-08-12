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
	double asimmetry_y{};
	double asimmetry_th{};
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
	double y2;
	double th2;
	double y3;
	double th3;
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
		gaps.y2 += (p.y - mean_y) * (p.y - mean_y);
		gaps.y3 += (p.y - mean_y) * (p.y - mean_y) * (p.y - mean_y);
		gaps.th2 += (p.theta - mean_th) * (p.theta - mean_th);
		gaps.th3 += (p.theta - mean_th) * (p.theta - mean_th) * (p.theta - mean_th);
	}

	double const asimmetry_y{(std::sqrt(N) * gaps.y3) / (gaps.y2 * std::sqrt(gaps.y2))};
	double const asimmetry_th{(std::sqrt(N) * gaps.th3) / (gaps.th2 * std::sqrt(gaps.th2))};

	/* cannot use mean_y and mean_theta
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

	return {mean_y, sigma_y, mean_th, sigma_th, asimmetry_y, asimmetry_th};
}

#endif // STATISTICS_HPP