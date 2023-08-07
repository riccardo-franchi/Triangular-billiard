#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <cmath>
#include <stdexcept>

struct Particle
{
public:
	Particle(double x0, double y0, double theta) : x{x0}, y{y0}, theta{theta} {}

	Particle(double y0, double theta) : Particle(0, y0, theta) {}

	double x{};
	double y{};
	double theta{};
};

#endif // PARTICLE_HPP