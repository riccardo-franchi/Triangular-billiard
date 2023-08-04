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
	const double d{m_l - m_particle.x};
	const double coeff_min{m_r2 * m_particle.y / d};
	const double coeff_max{m_r1 * m_particle.y / d};

	const double coeff{std::tan(m_particle.theta)};

	if (coeff < coeff_max || coeff > coeff_min)
	{
		return false;
	}

	double yl{tan(m_particle.theta) * (m_l - m_particle.x) + m_particle.y};

	if (-m_r2 < yl < m_r2)
	{
		return false;
	}

	return true;
}

void Billiard::calcTrajectory()
{
	const double coeff{std::tan(m_particle.theta)};
	const double alpha{std::atan((m_r2 - m_r1) / m_l)};

	// These expressions are correct only for the upper wall
	double yl{tan(m_particle.theta) * (m_l - m_particle.x) + m_particle.y};

	double xi{m_particle.x};

	if (yl > m_r2)
	{
		xi = (coeff * m_particle.x + m_r1 - m_particle.y) / (coeff + ((m_r1 - m_r2) / m_l));
	}
	else
	{
		xi = (coeff * m_particle.x - m_r1 - m_particle.y) / (coeff + ((m_r2 - m_r1) / m_l));
	}
	const double yi{coeff * (xi - m_particle.x) + m_particle.y};
	const double theta{2. * alpha - m_particle.theta};
	m_particle = {xi, yi, theta};
}
