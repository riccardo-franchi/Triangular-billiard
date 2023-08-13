#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "particle.hpp"

#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>

class Statistics
{
public:
	struct Stats
	{
		double mean{};
		double sigma{};
		double skewness{};
		double kurtosis{};
	};
	struct Results
	{
		Stats y{};
		Stats theta{};
	};

	Statistics(const double l) : m_l{l} {}

	int getN() const { return m_N; }

	Results operator()(const std::vector<Particle>& particles);

private:
	const double m_l{};

	int m_N{};
};

#endif // STATISTICS_HPP