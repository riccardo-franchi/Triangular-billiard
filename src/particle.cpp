#include "../include/particle.hpp"
#include "../include/billiard.hpp"
#include "../include/point.hpp"

Particle::Particle(double y0, double v0x, double v0y) //
	: m_p{0., y0}, m_vx{v0x}, m_vy{v0y} {};

Particle collision(Particle particle, Billiard billiard)
{
	if (particle.getVy() > 0 || (particle.getVy() == 0 && particle.getPoint().y >= billiard.getR2()))
	{
		Particle particleF{particle};
		double xu{
			(particle.getVy() * particle.getPoint().x / particle.getVx() + billiard.getR1() - particle.getPoint().y) /
			(particle.getVy() / particle.getVx() + (billiard.getR1() - billiard.getR2()) / billiard.getL())};
		double yu{particle.getVy() * (xu - particle.getPoint().x) / particle.getVx() + particle.getPoint().y};
		particleF.setPoint(xu, yu);
		double vxf{
			// necessario introdurre theta?
		};
		particleF.setVx(vxf);
		double vyf{
			// necessario introdurre theta?
		};
		particleF.setVy(vyf);
		particle = particleF;
	}
}