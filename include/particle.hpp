#ifndef PARTICLE_HPP
#define PARTICLE_HPP

class Particle
{
public:
	Particle(double y0, double theta);
	double getX() const { return m_x; }
	double getY() const { return m_y; }
	double getTheta() const { return m_theta; }
	void setX(double x) { m_x = x; }
	void setY(double y) { m_y = y; }
	void setTheta(double theta) { m_theta = theta; }

private:
	double m_x;
	double m_y;
	double m_theta;
};

bool collide(Particle particle, Billiard billiard);

#endif // PARTICLE_HPP