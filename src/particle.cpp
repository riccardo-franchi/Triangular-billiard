#include "../include/particle.hpp"
#include "../include/billiard.hpp"
#include "../include/point.hpp"

#include <cmath>
#include <stdexcept>

Particle::Particle(double y0, double theta) : m_p{0., y0}, m_theta{theta} //
{
	if (theta > M_PI / 2 || theta < -M_PI / 2)
	{
		throw std::domain_error("Invalid angle");
	}
};

bool collide(Particle particle, Billiard billiard)
{

	// check if the particle excapes the billiard
	double theta_min{billiard.getR2() * particle.getPoint().y / (billiard.getL() - particle.getPoint().x)};
	double theta_max{billiard.getR1() * particle.getPoint().y / (billiard.getL() - particle.getPoint().x)};
	if (particle.getTheta() < theta_max || particle.getTheta() > theta_min)
	{
		return false;
	}
	else
	{
		return true;
	}
}