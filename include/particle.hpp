#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <cmath>
#include <stdexcept>

class Particle
{
public:
	Particle(double y0, double theta) : m_x{0}, m_y{y0}, m_theta{theta}
	{
		if (theta > M_PI / 2 || theta < -M_PI / 2)
		{
			throw std::domain_error("Invalid angle");
		}
	}

	double getX() const { return m_x; }
	double getY() const { return m_y; }
	double getTheta() const { return m_theta; }

	void setX(double x) { m_x = x; }
	void setY(double y) { m_y = y; }
	void setTheta(double theta) { m_theta = theta; }

private:
	double m_x{};
	double m_y{};
	double m_theta{};
};

#endif // PARTICLE_HPP