#include "../include/particle.hpp"
#include "../include/billiard.hpp"
#include "../include/point.hpp"

#include <cmath>
#include <stdexcept>

Particle::Particle(double y0, double theta) : m_p{0., y0}, m_theta{theta} //
{
	if (theta > M_PI / 2 || theta < -M_PI / 2)
	{
		throw std::domain_error("Invalid angol");
	}
};

Particle collision(Particle particle, Billiard billiard) {}