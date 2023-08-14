#include "../include/statistics.hpp"

#include <cmath>
#include <numeric>
#include <stdexcept>

struct Sums
{
	double x{};
	double x2{};
};

struct Moments
{
	double x3{};
	double x4{};
};

Statistics::Results Statistics::operator()(const std::vector<Particle>& particles)
{
	// Create vector of y and theta values of escaped particles
	std::vector<double> y{};
	std::vector<double> theta{};
	y.reserve(particles.size());
	theta.reserve(particles.size());
	for (const auto& p : particles)
	{
		if (p.x == m_l)
		{
			y.push_back(p.y);
			theta.push_back(p.theta);
		}
	}
	y.shrink_to_fit();
	theta.shrink_to_fit();

	m_N = static_cast<int>(y.size());

	if (m_N < 2)
	{
		throw std::runtime_error{"Not enough entries to compute statistics"};
	}

	return {computeStats(y), computeStats(theta)};
}

Statistics::Stats Statistics::computeStats(const std::vector<double>& data)
{

	const Sums sums{std::accumulate(data.begin(), data.end(), Sums{},
									[](Sums s, double x)
									{
										s.x += x;
										s.x2 += x * x;
										return s;
									})};

	const double mean{sums.x / m_N};
	const double sigma{std::sqrt((sums.x2 - m_N * mean * mean) / (m_N - 1))};

	const Moments gaps{std::accumulate(data.begin(), data.end(), Moments{},
									   [mean](Moments m, double x)
									   {
										   const double gap{x - mean};
										   m.x3 += std::pow(gap, 3);
										   m.x4 += std::pow(gap, 4);
										   return m;
									   })};

	const double skewness{gaps.x3 / (m_N * std::pow(sigma, 3))};
	const double kurtosis{gaps.x4 / (m_N * std::pow(sigma, 4))};

	return {mean, sigma, skewness, kurtosis};
}