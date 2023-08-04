#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include <cmath>

struct Particle
{
public:
	Particle(double x0, double y0, double theta) : x{x0}, y{y0}, theta{theta}
	{
		if (std::abs(theta) > M_PI / 2)
		{
			throw std::domain_error{"Invalid angle"};
		}
	}
	Particle(double y0, double theta) : Particle(0, y0, theta)
	{
		if (std::abs(theta) > M_PI / 2)
		{
			throw std::domain_error{"Invalid angle"};
		}
	}

	double x{};
	double y{};
	double theta{};
};

#endif // PARTICLE_HPP