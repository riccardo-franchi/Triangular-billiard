#ifndef BILLIARD_HPP
#define BILLIARD_HPP

#include "particle.hpp"
#include <stdexcept>

class Billiard
{
public:
	Billiard(const double r1, const double r2, const double l);

	double getR1() const { return m_r1; }
	double getR2() const { return m_r2; }
	double getL() const { return m_l; }

	void runSimulation();

private:
	bool collide();
	void trajectory();

	double m_r1{};
	double m_r2{};
	double m_l{};

	Particle particle{0, 0};
};

#endif // BILLIARD_HPP