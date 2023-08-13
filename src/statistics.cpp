#include "../include/statistics.hpp"

Statistics::Results Statistics::operator()(const std::vector<Particle>& particles)
{
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

	// Copy all the particles that have escaped the billiard
	std::vector<Particle> escParts{};
	escParts.reserve(particles.size());
	std::remove_copy_if(particles.begin(), particles.end(), std::back_inserter(escParts),
						[this](const Particle& p) { return p.x < m_l; });
	escParts.shrink_to_fit();

	m_N = static_cast<int>(escParts.size());

	if (m_N < 2)
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

	const double mean_y{sums.yf / m_N};
	const double sigma_y{std::sqrt((sums.yf2 - m_N * mean_y * mean_y) / (m_N - 1))};	// why not mean sigma?
	const double mean_th{sums.th / m_N};
	const double sigma_th{std::sqrt((sums.th2 - m_N * mean_th * mean_th) / (m_N - 1))}; // idem

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

	const double skewness_y{gaps.y3 / (m_N * sigma_y * sigma_y * sigma_y)};
	const double skewness_th{gaps.th3 / (m_N * sigma_th * sigma_th * sigma_th)};
	const double kurtosis_y{gaps.y4 / (m_N * sigma_y * sigma_y * sigma_y * sigma_y)};
	const double kurtosis_th{gaps.th4 / (m_N * sigma_th * sigma_th * sigma_th * sigma_th)};

	return {{mean_y, sigma_y, skewness_y, kurtosis_y}, {mean_th, sigma_th, skewness_th, kurtosis_th}};
}