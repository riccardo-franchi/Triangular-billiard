#include "../include/particle.hpp"
#include "../include/billiard.hpp"
#include "../include/point.hpp"

Particle::Particle(double x, double y, double vx, double vy) : m_p{x, y}, m_vx{vx}, m_vy{vy} {}

Particle collision(Particle particle, Billiard billiard) {}