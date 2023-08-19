#ifndef BILLIARD_HPP
#define BILLIARD_HPP

#include "particle.hpp"

#include <vector>

namespace tb
{
class Billiard
{
public:
	Billiard() = default;
	Billiard(double r1, double r2, double l);

	double getR1() const { return m_r1; }
	double getL() const { return m_l; }
	void setL(double l) { m_l = l; }

	// Needed to use STL algorithms
	using value_type = Particle;
	void push_back(const Particle& particle);

	const std::vector<Particle>& getParticles() const { return m_particles; }
	std::vector<Particle> getEscapedParticles() const;
	const Particle& getParticle(int i) const { return m_particles.at(i); }

	bool empty() const { return m_particles.empty(); }
	int size() const { return m_particles.size(); }
	void clear() { m_particles.clear(); }

	void runSimulation();

private:
	Particle calcTrajectory(const Particle& p, const double alpha);

	double m_r1{1.};
	double m_r2{1.};
	double m_l{1.};

	std::vector<Particle> m_particles{};
};
} // namespace tb

#endif // BILLIARD_HPP