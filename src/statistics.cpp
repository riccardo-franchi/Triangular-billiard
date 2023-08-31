#include "../include/statistics.hpp"

#include <cmath>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <stdexcept>

namespace tb
{
struct Moments
{
	double x2{};
	double x3{};
	double x4{};
};

Stats computeStats(const std::vector<double>& data)
{
	const int N{static_cast<int>(data.size())};

	const double sum{std::accumulate(data.begin(), data.end(), 0., [](double s, double x) { return s += x; })};
	const double mean{sum / N};

	const Moments moments{std::accumulate(data.begin(), data.end(), Moments{},
										  [mean](Moments m, double x)
										  {
											  const double gap{x - mean};
											  const double gap2{gap * gap};
											  const double gap3{gap2 * gap};
											  const double gap4{gap3 * gap};

											  m.x2 += gap2;
											  m.x3 += gap3;
											  m.x4 += gap4;
											  return m;
										  })};

	const double sigma{std::sqrt(moments.x2 / (N - 1))};
	const double skewness{moments.x3 / (N * std::pow(sigma, 3))};
	const double kurtosis{moments.x4 / (N * std::pow(sigma, 4))};

	return {mean, sigma, skewness, kurtosis};
}

Results statistics(const std::vector<Particle>& particles)
{
	const auto N{particles.size()};

	if (N < 2)
	{
		throw std::runtime_error{"Not enough particles to compute statistics: " + std::to_string(N) +
								 "particle(s) escaped the billiard"};
	}

	std::vector<double> y{};
	std::vector<double> theta{};
	y.reserve(N);
	theta.reserve(N);
	for (const auto& p : particles)
	{
		y.push_back(p.y);
		theta.push_back(p.theta);
	}

	return {computeStats(y), computeStats(theta), static_cast<int>(N)};
}

std::string statsToString(const Results& stats)
{
	constexpr int w{20};
	std::ostringstream oss{};

	oss << std::setw(w) << std::left << "y_f mean: " << stats.y.mean << '\n'				 //
		<< std::setw(w) << std::left << "y_f sigma: " << stats.y.sigma << '\n'				 //
		<< std::setw(w) << std::left << "y_f skewness: " << stats.y.skewness << '\n'		 //
		<< std::setw(w) << std::left << "y_f kurtosis: " << stats.y.kurtosis << '\n'		 //
		<< std::setw(w) << std::left << "theta_f mean: " << stats.theta.mean << '\n'		 //
		<< std::setw(w) << std::left << "theta_f sigma: " << stats.theta.sigma << '\n'		 //
		<< std::setw(w) << std::left << "theta_f skewness: " << stats.theta.skewness << '\n' //
		<< std::setw(w) << std::left << "theta_f kurtosis: " << stats.theta.kurtosis << '\n';

	return oss.str();
}
} // namespace tb