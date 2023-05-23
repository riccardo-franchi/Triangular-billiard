#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "point.hpp"

class Particle
{
public:
	Particle(double x, double y, double vx, double vy);

private:
	Point m_p;
	double m_vx;
	double m_vy;
};

#endif