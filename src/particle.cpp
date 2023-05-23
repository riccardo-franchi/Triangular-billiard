#include "../include/particle.hpp"
#include "../include/billiard.hpp"
#include "../include/point.hpp"

Particle::Particle(double y0, double v0x, double v0y) //
	: m_p{0., y0}, m_vx{v0x}, m_vy{v0y} {};

Particle collision(Particle particle, Billiard billiard) {}