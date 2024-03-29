#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "particle.hpp"

#include <string>
#include <vector>

namespace tb
{
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
	int n{};
};

Results statistics(const std::vector<Particle>& particles);

std::string statsToString(const Results& stats);
} // namespace tb

#endif // STATISTICS_HPP