#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "point.hpp"

class Particle
{
public:
	Particle(double y0);

private:
	Point m_p0;
};

#endif // PARTICLE_HPP