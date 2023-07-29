#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "point.hpp"

class Particle
{
public:
	Particle(double y0, double v0x, double v0y);
	Point getPoint() const { return m_p; }
	double getVx() const { return m_vx; }
	double getVy() const { return m_vy; }
	void setPoint(double x, double y)
	{
		m_p.x = x;
		m_p.y = y;
	}
	void setVx(double vx) { m_vx = vx; }
	void setVy(double vy) { m_vy = vy; }

private:
	Point m_p;
	double m_vx;
	double m_vy;
};

#endif // PARTICLE_HPP