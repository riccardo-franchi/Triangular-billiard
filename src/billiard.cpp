#include "../include/billiard.hpp"

#include <algorithm>
#include <execution>

Billiard::Billiard(double r1, double r2, double l) //
	: m_r1{r1}, m_r2{r2}, m_l{l}
{
	if (m_r1 < 0 || m_r2 < 0 || m_l < 0)
	{
		throw std::domain_error{"Negative argument in constructor"};
	}
}

void Billiard::push_back(const Particle& particle)
{
	if (std::abs(particle.theta) > M_PI_2)
	{
		throw std::domain_error{"Invalid angle"};
	}
	m_particles.push_back(particle);
}

const std::vector<Particle>& Billiard::runSimulation()
{
	const double alpha{std::atan((m_r2 - m_r1) / m_l)};

	std::transform(/*std::execution::par_unseq,*/ m_particles.begin(), m_particles.end(), m_particles.begin(),
				   [&](const Particle& p) { return calcTrajectory(p, alpha); });

	return m_particles;
}

Particle Billiard::calcTrajectory(const Particle& p, const double alpha)
{
	Particle particle{p};
	double coeff{std::tan(particle.theta)};
	double yl{coeff * (m_l - particle.x) + particle.y};

	while (std::abs(yl) > m_r2)
	{
		const double theta{(yl > m_r2) ? 2. * alpha - particle.theta //
									   : -2. * alpha - particle.theta};

		if (std::abs(theta) > M_PI_2)
		{
			// end loop if the particle is going to move backwards
			return particle;
		}

		// True if the the collision happens with the upper wall, false with the lower wall
		const double xi{(yl > m_r2) ? (coeff * particle.x + m_r1 - particle.y) / (coeff + ((m_r1 - m_r2) / m_l))
									: (coeff * particle.x - m_r1 - particle.y) / (coeff + ((m_r2 - m_r1) / m_l))};

		const double yi{coeff * (xi - particle.x) + particle.y};

		particle = {xi, yi, theta};

		coeff = std::tan(particle.theta);
		yl = coeff * (m_l - particle.x) + particle.y;
	}

	// Set the final coords
	particle.x = m_l;
	particle.y = yl;

	return particle;
}