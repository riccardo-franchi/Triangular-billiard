#ifndef BILLIARD_HPP
#define BILLIARD_HPP

#include "particle.hpp"

class Billiard
{
public:
	Billiard(double r1, double r2, double l);

	void setParticle(const Particle& particle) { m_particle = particle; }

	double getR1() const { return m_r1; }
	double getR2() const { return m_r2; }
	double getL() const { return m_l; }

	void runSimulation();

private:
	bool willCollide();
	void calcTrajectory();

	double m_r1{};
	double m_r2{};
	double m_l{};

	Particle m_particle{0, 0};
};

#endif // BILLIARD_HPP