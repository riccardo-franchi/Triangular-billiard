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

	int size() const { return m_particles.size(); }
	void clear() { m_particles.clear(); }
	void reserve(int n) { m_particles.reserve(n); }
	void shrink_to_fit() { m_particles.shrink_to_fit(); }

	bool isParticleValid(const Particle& particle) const
	{
		return (std::abs(particle.y) < m_r1 && std::abs(particle.theta) < M_PI_2);
	};

	void runSimulation();

private:
	Particle calcTrajectory(Particle particle, double alpha);

	double m_r1{5.};
	double m_r2{3.};
	double m_l{13.};

	std::vector<Particle> m_particles{};
};
} // namespace tb

#endif // BILLIARD_HPP