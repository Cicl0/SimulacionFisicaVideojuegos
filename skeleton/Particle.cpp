#include "Particle.h"

Particle::Particle(Vector3 Pos = { 0.0f, 0.0f, 0.0f }, Vector3 Vel = {0.0f, 0.0f, 0.0f}, Vector3 Acc = {0.0f, 0.0f, 0.0f}, float Mass = 0) :
	pos(Pos),
	vel(Vel),
	acc(Acc),
	mass(0)
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
	renderItem = new RenderItem(shape, &pos, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
}

void Particle::integrate(double t) {
	vel += t * acc; // Calculo velocidad i + 1
	pos.p += (t * vel); // Calculo posicion i + 1
}