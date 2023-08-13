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
	double yf{};
	double yf2{};
	double th{};
	double th2{};
};

struct Gaps
{
	double y3{};
	double th3{};
	double y4{};
	double th4{};
};

Statistics statistics(const std::vector<Particle>& particles, const double l)
{
	// Copy all the particles that have escaped the billiard
	std::vector<Particle> escParts{};
	escParts.reserve(particles.size());
	std::remove_copy_if(particles.begin(), particles.end(), std::back_inserter(escParts),
						[l](const Particle& p) { return p.x < l; });
	escParts.shrink_to_fit();

	const int N{static_cast<int>(escParts.size())};

	if (N < 2)
	{
		throw std::runtime_error{"Not enough entries to run a statistics"};
	}

	const Sums sums{std::accumulate(escParts.begin(), escParts.end(), Sums{},
									[](Sums s, Particle p)
									{
										s.yf += p.y;
										s.yf2 += p.y * p.y;
										s.th += p.theta;
										s.th2 += p.theta * p.theta;
										return s;
									})};

	const double mean_y{sums.yf / N};
	const double sigma_y{std::sqrt((sums.yf2 - N * mean_y * mean_y) / (N - 1))};	// why not mean sigma?
	const double mean_th{sums.th / N};
	const double sigma_th{std::sqrt((sums.th2 - N * mean_th * mean_th) / (N - 1))}; // idem

	const Gaps gaps{std::accumulate(escParts.begin(), escParts.end(), Gaps{},
									[mean_y, mean_th](Gaps g, Particle p)
									{
										g.y3 += (p.y - mean_y) * (p.y - mean_y) * (p.y - mean_y);
										g.y4 += (p.y - mean_y) * (p.y - mean_y) * (p.y - mean_y) * (p.y - mean_y);
										g.th3 += (p.theta - mean_th) * (p.theta - mean_th) * (p.theta - mean_th);
										g.th4 += (p.theta - mean_th) * (p.theta - mean_th) * (p.theta - mean_th) *
												 (p.theta - mean_th);
										return g;
									})};

	const double skewness_y{gaps.y3 / (N * sigma_y * sigma_y * sigma_y)};
	const double skewness_th{gaps.th3 / (N * sigma_th * sigma_th * sigma_th)};
	const double kurtosis_y{gaps.y4 / (N * sigma_y * sigma_y * sigma_y * sigma_y)};
	const double kurtosis_th{gaps.th4 / (N * sigma_th * sigma_th * sigma_th * sigma_th)};

	return {mean_y, sigma_y, mean_th, sigma_th, skewness_y, skewness_th, kurtosis_y, kurtosis_th};
}

#endif // STATISTICS_HPP