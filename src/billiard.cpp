#include "../include/billiard.hpp"

#include <cmath>
#include <stdexcept>

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

	double coeff{std::tan(m_particle.theta)};

	while (willCollide(coeff))
	{
		if (std::abs(m_particle.theta) >= M_PI + alpha)
		{
			// end loop if the particle is going to move backwards
			break;
		}

		calcTrajectory(coeff, alpha);
		coeff = std::tan(m_particle.theta);
	}
}

bool Billiard::willCollide(const double coeff)
{

	const double yl{coeff * (m_l - m_particle.x) + m_particle.y};

	if (std::abs(yl) < m_r2)
	{
		// Set the final coords
		m_particle.x = m_l;
		m_particle.y = yl;

		return false;
	}

	return true;
}

void Billiard::calcTrajectory(const double coeff, const double alpha)
{
	const double yl{tan(m_particle.theta) * (m_l - m_particle.x) + m_particle.y};

	if (yl > m_r2) // the particle hits the upper edge
	{
		const double xi{(coeff * m_particle.x + m_r1 - m_particle.y) / (coeff + ((m_r1 - m_r2) / m_l))};
		const double theta{2. * alpha - m_particle.theta};
		const double yi{coeff * (xi - m_particle.x) + m_particle.y};
		m_particle = {xi, yi, theta};
	}
	else // the particle hits the lower edge
	{
		const double xi{(coeff * m_particle.x - m_r1 - m_particle.y) / (coeff + ((m_r2 - m_r1) / m_l))};
		const double theta{-2. * alpha - m_particle.theta};
		const double yi{coeff * (xi - m_particle.x) + m_particle.y};
		m_particle = {xi, yi, theta};
	}
}
