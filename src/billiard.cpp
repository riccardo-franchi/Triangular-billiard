#include "../include/billiard.hpp"

#include <stdexcept>

Billiard::Billiard(double r1, double r2, double l) //
	: m_r1{r1}, m_r2{r2}, m_l{l}
{
	if (m_r1 < 0 || m_r2 < 0 || m_l < 0)
	{
		throw std::domain_error("Negative argument in constructor");
	}
}

void Billiard::runSimulation()
{
	while (collide())
	{
		trajectory();
	}
}

bool Billiard::collide()
{
	double coeff_min{m_r2 * m_particle.getY() / (m_l - m_particle.getX())};
	double coeff_max{m_r1 * m_particle.getY() / (m_l - m_particle.getX())};
	if (std::tan(m_particle.getTheta()) < coeff_max || std::tan(m_particle.getTheta()) > coeff_min)
	{
		return false;
	}

	return true;
}

void Billiard::trajectory()
{
	Particle m_particleF{m_particle};
	double xu{(std::tan(m_particle.getTheta()) * m_particle.getX() + m_r1 - m_particle.getY()) /
			  (std::tan(m_particle.getTheta()) + ((m_r1 - m_r2) / m_l))};
	double yu{};
	m_particleF.setX(xu);
	m_particleF.setY(yu);
	double theta{
		// da fare
	};
	m_particleF.setTheta(theta);
	m_particle = m_particleF;
}