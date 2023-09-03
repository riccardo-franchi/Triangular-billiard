#ifndef BILLIARD_HPP
#define BILLIARD_HPP

#include "particle.hpp"

#include <cmath>
#include <vector>

namespace tb
{
enum class BilliardType
{
	Linear,
	Parabolic,
	Semicircular
};

class Billiard
{
public:
	Billiard() = default;
	Billiard(double r1, double r2, double l, BilliardType type = BilliardType::Linear, double e = 1.);

	double getR1() const { return m_r1; }
	double getL() const { return m_l; }
	void setL(double l) { m_l = l; }

	const std::vector<Particle>& getParticles() const { return m_particles; }
	std::vector<Particle> getEscapedParticles() const;
	const Particle& getParticle(int i) const { return m_particles.at(i); }

	void push_back(const Particle& particle);
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
	Particle calcLinearTrajectory(Particle particle, double alpha) const;
	Particle calcParabolicTrajectory(Particle particle, double k) const;
	Particle calcCircularTrajectory(Particle particle, double R) const;

	double updateAngle(double theta, double alpha, bool isUpperWall) const;

	double m_r1{5.};
	double m_r2{3.};
	double m_l{13.};

	BilliardType m_type{BilliardType::Linear};

	double m_e{1.};

	std::vector<Particle> m_particles{};
};
} // namespace tb

#endif // BILLIARD_HPP