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
	calcTrajectory(alpha);
}

void Billiard::calcTrajectory(const double alpha)
{
	double coeff{std::tan(m_particle.theta)};
	double yl{coeff * (m_l - m_particle.x) + m_particle.y};

	while (std::abs(yl) > m_r2)
	{
		if (std::abs(m_particle.theta) >= M_PI + alpha)
		{
			// end loop if the particle is going to move backwards
			return;
		}

		// True if the the collision happens with the upper wall, false with the lower wall
		const double xi{(yl > m_r2) ? (coeff * m_particle.x + m_r1 - m_particle.y) / (coeff + ((m_r1 - m_r2) / m_l))
									: (coeff * m_particle.x - m_r1 - m_particle.y) / (coeff + ((m_r2 - m_r1) / m_l))};

		const double theta{(yl > m_r2) ? 2. * alpha - m_particle.theta //
									   : -2. * alpha - m_particle.theta};

		const double yi{coeff * (xi - m_particle.x) + m_particle.y};

		m_particle = {xi, yi, theta};

		coeff = std::tan(m_particle.theta);
		yl = coeff * (m_l - m_particle.x) + m_particle.y;
	}

	// Set the final coords
	m_particle.x = m_l;
	m_particle.y = yl;
}