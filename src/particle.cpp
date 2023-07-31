#include "../include/particle.hpp"
#include "../include/billiard.hpp"

#include <cmath>
#include <stdexcept>

Particle::Particle(double y0, double theta) : m_x{0}, m_y{y0}, m_theta{theta}
{
	if (theta > M_PI / 2 || theta < -M_PI / 2)
	{
		throw std::domain_error("Invalid angle");
	}
};

bool collide(Particle particle, const Billiard billiard)
{
	// check if the particle stays in the billiard
	double coeff_min{billiard.getR2() * particle.getY() / (billiard.getL() - particle.getX())};
	double coeff_max{billiard.getR1() * particle.getY() / (billiard.getL() - particle.getX())};
	if (tan(particle.getTheta()) < coeff_max || tan(particle.getTheta()) > coeff_min)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void trajectory(Particle& particle, const Billiard billiard)
{
	Particle particleF{particle};
	double xu{(tan(particle.getTheta()) * particle.getX() + billiard.getR1() - particle.getY()) /
			  (tan(particle.getTheta()) + ((billiard.getR1() - billiard.getR2()) / billiard.getL()))};
	double yu{};
	particleF.setX(xu);
	particleF.setY(yu);
	double theta{
		// da fare
	};
	particleF.setTheta(theta);
	particle = particleF;
}

void runSimulation(Particle& particle, const Billiard billiard)
{
	while (collide(particle, billiard))
	{
		trajectory(particle, billiard);
	}
}