#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "point.hpp"

class Particle
{
public:
	Particle(double y0, double v0x, double v0y);

private:
	Point m_p;
	double m_vx;
	double m_vy;
};

#endif // PARTICLE_HPP