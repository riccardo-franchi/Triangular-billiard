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
	while (willCollide())
	{
		calcTrajectory();
	}
}

bool Billiard::willCollide()
{
	const double coeff{std::tan(m_particle.theta)};

	const double yl{tan(m_particle.theta) * (m_l - m_particle.x) + m_particle.y};

	if (std::abs(yl) < m_r2)
	{
		// Set the final coords
		m_particle.x = m_l;
		m_particle.y = yl;

		return false;
	}

	return true;
}

void Billiard::calcTrajectory()
{
	const double coeff{std::tan(m_particle.theta)};
	const double alpha{std::atan((m_r2 - m_r1) / m_l)};

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
