#include "billiard.hpp"

Billiard::Billiard(const double r1, const double r2, const double l) //
	: m_r1{r1}, m_r2{r2}, m_l{l}									 //
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
	double coeff_min{m_r2 * particle.getY() / (m_l - particle.getX())};
	double coeff_max{m_r1 * particle.getY() / (m_l - particle.getX())};
	if (std::tan(particle.getTheta()) < coeff_max || std::tan(particle.getTheta()) > coeff_min)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Billiard::trajectory()
{
	Particle particleF{particle};
	double xu{(std::tan(particle.getTheta()) * particle.getX() + m_r1 - particle.getY()) /
			  (std::tan(particle.getTheta()) + ((m_r1 - m_r2) / m_l))};
	double yu{};
	particleF.setX(xu);
	particleF.setY(yu);
	double theta{
		// da fare
	};
	particleF.setTheta(theta);
	particle = particleF;
}