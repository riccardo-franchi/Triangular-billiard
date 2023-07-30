#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <numbers>
#include <stdexcept>

class Particle
{
public:
	explicit Particle(double y0, double theta) : m_x0{0.0}, m_y0{y0}, m_theta{theta}
	{
		if (m_theta < -std::numbers::pi || m_theta > std::numbers::pi)
		{
			throw std::invalid_argument{"theta must be in [-pi, pi]"};
		}
	}

private:
	double m_x0;
	double m_y0;
	double m_theta;
};

#endif // PARTICLE_HPP