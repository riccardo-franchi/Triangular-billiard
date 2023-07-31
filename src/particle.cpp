#include "../include/particle.hpp"
#include "../include/billiard.hpp"

#include <cmath>
#include <stdexcept>

Particle::Particle(double y0, double theta) : m_x{0}, m_y{y0}, m_theta{theta} //
{
	if (theta > M_PI / 2 || theta < -M_PI / 2)
	{
		throw std::domain_error("Invalid angle");
	}
};

bool collide(Particle particle, Billiard billiard)
{
	// check if the particle stays in the billiard
	double theta_min{billiard.getR2() * particle.getY() / (billiard.getL() - particle.getX())};
	double theta_max{billiard.getR1() * particle.getY() / (billiard.getL() - particle.getX())};
	if (particle.getTheta() < theta_max || particle.getTheta() > theta_min)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void runSimulation(Particle particle, Billiard billiard)
{
	while (collide(particle, billiard))
	{
		// trajectory function
		collide(particle, billiard);
	}
}