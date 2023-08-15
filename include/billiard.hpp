#ifndef BILLIARD_HPP
#define BILLIARD_HPP

#include "particle.hpp"

#include <vector>

namespace bs
{
class Billiard
{
public:
	Billiard(double r1, double r2, double l);

	// Needed to use std::generate
	using value_type = Particle;
	void push_back(const Particle& particle);

	const std::vector<Particle>& getParticles() const { return m_particles; }
	const Particle& getParticle(int i) const { return m_particles.at(i); }

	double getL() const { return m_l; }
	double getR1() const { return m_r1; }
	// const double getR2() const { return m_r2; }

	bool empty() const { return m_particles.empty(); }
	int size() const { return m_particles.size(); }
	void clear() { m_particles.clear(); }

	const std::vector<Particle>& runSimulation();

private:
	Particle calcTrajectory(const Particle& p, const double alpha);

	double m_r1{};
	double m_r2{};
	double m_l{};

	std::vector<Particle> m_particles{};
};
} // namespace bs

#endif // BILLIARD_HPP