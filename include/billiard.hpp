#ifndef BILLIARD_HPP
#define BILLIARD_HPP

#include "particle.hpp"

#include <vector>

class Billiard
{
public:
	Billiard(double r1, double r2, double l);

	// Needed to use std::generate
	using value_type = Particle;
	void push_back(const Particle& particle);

	const std::vector<Particle>& getParticles() const { return m_particles; }
	const Particle& getParticle(int i) const { return m_particles.at(i); }

	bool empty() const { return m_particles.empty(); }
	int size() const { return m_particles.size(); }
	void clear() { m_particles.clear(); }
	double getL() {return m_r1; }

	void runSimulation();

private:
	Particle calcTrajectory(const Particle& p, const double alpha);

	double m_r1{};
	double m_r2{};
	double m_l{};

	std::vector<Particle> m_particles{};
};

#endif // BILLIARD_HPP