#include "../include/statistics.hpp"

#include <cmath>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>

namespace bs
{
struct Moments
{
	double x2{};
	double x3{};
	double x4{};
};

Statistics::Results Statistics::operator()(const std::vector<Particle>& particles)
{
	if (particles.size() < 2)
	{
		throw std::runtime_error{"Not enough particles to compute statistics"};
	}

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
		throw std::runtime_error{"Cannot compute statistics: " + std::to_string(m_N) + " particle(s) escaped"};
	}

	return {computeStats(y), computeStats(theta)};
}

std::string Statistics::statsToString(const Results& stats)
{
	const int w{20};
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

Statistics::Stats Statistics::computeStats(const std::vector<double>& data)
{
	const double sum{std::accumulate(data.begin(), data.end(), 0., [](double s, double x) { return s += x; })};
	const double mean{sum / m_N};

	const Moments moments{std::accumulate(data.begin(), data.end(), Moments{},
										  [mean](Moments m, double x)
										  {
											  const double gap{x - mean};
											  m.x2 += std::pow(gap, 2);
											  m.x3 += std::pow(gap, 3);
											  m.x4 += std::pow(gap, 4);
											  return m;
										  })};

	const double sigma{std::sqrt(moments.x2 / (m_N - 1))};
	const double skewness{moments.x3 / (m_N * std::pow(sigma, 3))};
	const double kurtosis{moments.x4 / (m_N * std::pow(sigma, 4))};

	return {mean, sigma, skewness, kurtosis};
}
} // namespace bs