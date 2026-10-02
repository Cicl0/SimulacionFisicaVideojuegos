#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel) :
	pos(Pos),
	vel(Vel),
	mass(0)
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
	renderItem = new RenderItem(shape, &pos, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
}

void Particle::integrate(double t) {
	pos.p += (t * vel); // integrate con velocidad constante
}