#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "particle.hpp"

#include <vector>

namespace bs
{
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
	Stats computeStats(const std::vector<double>& data);

	const double m_l{};

	int m_N{};
};
} // namespace bs
#endif // STATISTICS_HPP