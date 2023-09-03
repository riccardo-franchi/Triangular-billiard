#include "../include/billiard.hpp"

#include <algorithm>
#include <execution>
#include <stdexcept>

namespace tb
{
Billiard::Billiard(double r1, double r2, double l, BilliardType type, double e)
	: m_r1{r1}, m_r2{r2}, m_l{l}, m_type{type}, m_e{e}
{
	if (m_r1 <= 0 || m_r2 <= 0 || m_l <= 0)
	{
		throw std::domain_error{"Billiard parameters must be positive"};
	}

	if (m_type == BilliardType::Semicircular && m_r1 <= m_r2)
	{
		throw std::domain_error{"For semicircular billiard, r1 must be greater than r2"};
	}

	if (m_e < 0 || m_e > 1)
	{
		throw std::domain_error{"Coefficient of restitution must be between 0 and 1"};
	}
}

std::vector<Particle> Billiard::getEscapedParticles() const
{
	std::vector<Particle> escapedParticles{};
	escapedParticles.reserve(m_particles.size());
	std::remove_copy_if(m_particles.begin(), m_particles.end(), std::back_inserter(escapedParticles),
						[this](const Particle& p) { return p.x < m_l; });
	escapedParticles.shrink_to_fit();
	return escapedParticles;
}

void Billiard::push_back(const Particle& particle)
{
	if (std::abs(particle.theta) > M_PI_2)
	{
		throw std::domain_error{"Invalid angle"};
	}
	if (std::abs(particle.y) > m_r1)
	{
		throw std::domain_error{"Invalid y coordinate"};
	}

	m_particles.push_back(particle);
}

void Billiard::runSimulation()
{
	if (size() == 0)
	{
		throw std::domain_error{"No particles to run"};
	}

	// If the number of particles is small, don't use parallel execution
	constexpr int maxSequentialParts{20'000};

	if (m_type == BilliardType::Linear)
	{
		const double alpha{std::atan((m_r2 - m_r1) / m_l)};
		if (size() < maxSequentialParts)
		{
			std::transform(m_particles.begin(), m_particles.end(), m_particles.begin(),
						   [&](const Particle& p) { return calcLinearTrajectory(p, alpha); });
		}
		else
		{
			std::transform(std::execution::par, m_particles.begin(), m_particles.end(), m_particles.begin(),
						   [&](const Particle& p) { return calcLinearTrajectory(p, alpha); });
		}
	}
	else if (m_type == BilliardType::Parabolic)
	{
		const double k{2. * (m_r1 - m_r2) / m_l};
		if (size() < maxSequentialParts)
		{
			std::transform(m_particles.begin(), m_particles.end(), m_particles.begin(),
						   [&](const Particle& p) { return calcParabolicTrajectory(p, k); });
		}
		else
		{
			std::transform(std::execution::par, m_particles.begin(), m_particles.end(), m_particles.begin(),
						   [&](const Particle& p) { return calcParabolicTrajectory(p, k); });
		}
	}
	else // Semicircular
	{
		const double R{(m_l * m_l + (m_r1 - m_r2) * (m_r1 - m_r2)) / (2. * (m_r1 - m_r2))};
		if (size() < maxSequentialParts)
		{
			std::transform(m_particles.begin(), m_particles.end(), m_particles.begin(),
						   [&](const Particle& p) { return calcCircularTrajectory(p, R); });
		}
		else
		{
			std::transform(std::execution::par, m_particles.begin(), m_particles.end(), m_particles.begin(),
						   [&](const Particle& p) { return calcCircularTrajectory(p, R); });
		}
	}
}

Particle Billiard::calcLinearTrajectory(Particle particle, double alpha) const
{
	double m{std::tan(particle.theta)};
	double yl{m * (m_l - particle.x) + particle.y};

	while (std::abs(yl) > m_r2)
	{
		const bool isUpperWall{yl > m_r2};

		const double theta{updateAngle(particle.theta, alpha, isUpperWall)};

		if (std::abs(theta) > M_PI_2)
		{
			// end loop if the particle is going to move backwards
			return particle;
		}

		// True if the the collision happens with the upper wall, false with the lower wall
		const double xi{isUpperWall ? (m * particle.x + m_r1 - particle.y) / (m + ((m_r1 - m_r2) / m_l))
									: (m * particle.x - m_r1 - particle.y) / (m + ((m_r2 - m_r1) / m_l))};

		const double yi{m * (xi - particle.x) + particle.y};

		particle = {xi, yi, theta};

		m = std::tan(particle.theta);
		yl = m * (m_l - particle.x) + particle.y;
	}

	// Set the final coords
	particle.x = m_l;
	particle.y = yl;

	return particle;
}

Particle Billiard::calcParabolicTrajectory(Particle particle, double k) const
{
	double m{std::tan(particle.theta)};
	double yl{m * (m_l - particle.x) + particle.y};

	while (std::abs(yl) > m_r2)
	{
		const bool isUpperWall{yl > m_r2};

		// True if the the collision happens with the upper wall, false with the lower wall
		const double numerator{
			isUpperWall ? k + m - std::sqrt((k + m) * (k + m) - 2. * k / m_l * (m * particle.x - particle.y + m_r1))
						: k - m - std::sqrt((k - m) * (k - m) + 2. * k / m_l * (m * particle.x - particle.y - m_r1))};
		const double xi{numerator * m_l / k};

		const double alpha{std::atan(k * (xi - m_l) / m_l)};
		const double theta{updateAngle(particle.theta, alpha, isUpperWall)};

		if (std::abs(theta) > M_PI_2)
		{
			// end loop if the particle is going to move backwards
			return particle;
		}

		const double yi{m * (xi - particle.x) + particle.y};

		particle = {xi, yi, theta};

		m = std::tan(particle.theta);
		yl = m * (m_l - particle.x) + particle.y;
	}

	// Set the final coords
	particle.x = m_l;
	particle.y = yl;

	return particle;
}

Particle Billiard::calcCircularTrajectory(Particle particle, double R) const
{
	double m{std::tan(particle.theta)};
	double yl{m * (m_l - particle.x) + particle.y};

	while (std::abs(yl) > m_r2)
	{
		const bool isUpperWall{yl > m_r2};

		// True if the the collision happens with the upper wall, false with the lower wall
		const double k{isUpperWall ? R + m_r2 - particle.y + m * particle.x //
								   : -R - m_r2 - particle.y + m * particle.x};
		const double a{m * m + 1.};
		const double b{m_l + m * k};
		const double xi{(b - std::sqrt(b * b - a * (k * k - R * R + m_l * m_l))) / a};

		const double yi{m * (xi - particle.x) + particle.y};

		const double alpha{std::atan((xi - m_l) / (R + m_r2 - yi))};
		const double theta{updateAngle(particle.theta, alpha, isUpperWall)};

		if (std::abs(theta) > M_PI_2)
		{
			// end loop if the particle is going to move backwards
			return particle;
		}

		particle = {xi, yi, theta};

		m = std::tan(particle.theta);
		yl = m * (m_l - particle.x) + particle.y;
	}

	// Set the final coords
	particle.x = m_l;
	particle.y = yl;

	return particle;
}
} // namespace tb

double tb::Billiard::updateAngle(double theta, double alpha, bool isUpperWall) const
{
	if (m_e == 1.)
	{
		return isUpperWall ? 2. * alpha - theta //
						   : -2. * alpha - theta;
	}

	return isUpperWall ? alpha - M_PI_2 + std::atan(1 / m_e * std::tan(M_PI_2 - theta + alpha)) //
					   : -alpha + M_PI_2 + std::atan(1 / m_e * std::tan(M_PI_2 - theta - alpha));
}
