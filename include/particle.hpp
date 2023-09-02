#ifndef PARTICLE_HPP
#define PARTICLE_HPP

namespace tb
{
struct Particle
{
public:
	Particle(double x0, double y0, double theta) : x{x0}, y{y0}, theta{theta} {}
	Particle(double y0, double theta) : Particle(0, y0, theta) {}

	double x{};
	double y{};
	double theta{};
};
} // namespace tb

#endif // PARTICLE_HPP