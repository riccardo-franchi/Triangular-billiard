#include "../include/billiard.hpp"

Billiard::Billiard(double r1, double r2, double l) //
	: m_r1{r1}, m_r2{r2}, m_l{l}
{
	if (m_r1 < 0 || m_r2 < 0 || m_l < 0)
	{
		throw std::domain_error{"Negative argument in constructor"};
	}
}

void Billiard::runSimulation()
{
	const double alpha{std::atan((m_r2 - m_r1) / m_l)};
	for (auto i{m_vector.begin()}; i != m_vector.end(); i++)
	{
		Particle& particle{*i};
		calcTrajectory(particle, alpha);
	}
}

void Billiard::calcTrajectory(Particle& particle, const double alpha)
{
	double coeff{std::tan(particle.theta)};
	double yl{coeff * (m_l - particle.x) + particle.y};

	while (std::abs(yl) > m_r2)
	{
		if (std::abs(particle.theta) >= M_PI + alpha)
		{
			// end loop if the particle is going to move backwards
			return;
		}

		// True if the the collision happens with the upper wall, false with the lower wall
		const double xi{(yl > m_r2) ? (coeff * particle.x + m_r1 - particle.y) / (coeff + ((m_r1 - m_r2) / m_l))
									: (coeff * particle.x - m_r1 - particle.y) / (coeff + ((m_r2 - m_r1) / m_l))};

		const double theta{(yl > m_r2) ? 2. * alpha - particle.theta //
									   : -2. * alpha - particle.theta};

		const double yi{coeff * (xi - particle.x) + particle.y};

		particle = {xi, yi, theta};

		coeff = std::tan(particle.theta);
		yl = coeff * (m_l - particle.x) + particle.y;
	}

	// Set the final coords
	particle.x = m_l;
	particle.y = yl;
}