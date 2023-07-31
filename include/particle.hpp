#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "point.hpp"

class Particle
{
public:
	Particle(double y0, double theta);
	Point getPoint() const { return m_p; }
	double getTheta() const { return m_theta; }
	void setPoint(double x, double y)
	{
		m_p.x = x;
		m_p.y = y;
	}
	void setTheta(double theta) { m_theta = theta; }

private:
	Point m_p;
	double m_theta;
};

bool collide(Particle particle, Billiard billiard);

#endif // PARTICLE_HPP