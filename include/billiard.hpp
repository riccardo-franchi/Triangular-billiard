#ifndef BILLIARD_HPP
#define BILLIARD_HPP

#include "particle.hpp"
#include <vector>

struct Statistics
{
	double mean{};
	double sigma{};
	double mean_err{};
	double median{};
};

struct Sums
{
	double x;
	double x2;
};

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

	void runSimulation();

	Statistics statistics(Sums sums) const;

private:
	Particle calcTrajectory(const Particle& p, const double alpha);

	double m_r1{};
	double m_r2{};
	double m_l{};

	std::vector<Particle> m_particles{};
};

#endif // BILLIARD_HPP