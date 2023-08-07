#ifndef BILLIARD_HPP
#define BILLIARD_HPP

#include "particle.hpp"
#include <vector>

class Billiard
{
public:
	// Needed to use std::generate
	using value_type = Particle;

	Billiard(double r1, double r2, double l);

	void push_back(const Particle& particle) { m_particles.push_back(particle); }

	const std::vector<Particle>& getParticles() const { return m_particles; }
	const Particle& getParticle(int i) const { return m_particles.at(i); }

	bool empty() const { return m_particles.empty(); }
	int size() const { return m_particles.size(); }
	void clear() { m_particles.clear(); }

	void runSimulation();

private:
	void calcTrajectory(Particle& particle, const double alpha);

	double m_r1{};
	double m_r2{};
	double m_l{};

	std::vector<Particle> m_particles{};
};

#endif // BILLIARD_HPP