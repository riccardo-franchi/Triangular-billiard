#ifndef BILLIARD_HPP
#define BILLIARD_HPP

#include "particle.hpp"
#include <vector>

class Billiard
{
public:
	Billiard(double r1, double r2, double l);

	bool empty();
	void pushback(const Particle& particle) { m_vector.push_back(particle); }
	std::vector<Particle> getVector() const { return m_vector; }

	double getR1() const { return m_r1; }
	double getR2() const { return m_r2; }
	double getL() const { return m_l; }

	void runSimulation();

private:
	void calcTrajectory(Particle& particle, const double alpha);

	double m_r1{};
	double m_r2{};
	double m_l{};

	std::vector<Particle> m_vector;
};

#endif // BILLIARD_HPP