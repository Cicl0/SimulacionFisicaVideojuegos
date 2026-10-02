#include "Particle.h"
#include <cmath> 

Particle::Particle(Vector3 Pos = { 0.0f, 0.0f, 0.0f }, Vector3 Vel = {0.0f, 0.0f, 0.0f}, Vector3 Acc = {0.0f, 0.0f, 0.0f}, float Mass = 0, float Damp = 0) :
	pos(Pos),
	vel(Vel),
	acc(Acc),
	mass(0)
{
	if (Damp > 1) damp = 1;
	else if (Damp < 0) damp = 0;
	else damp = Damp;

	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
	renderItem = new RenderItem(shape, &pos, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
}

void Particle::integrate(double t) {
	vel += t * acc; // Calculo velocidad i + 1
	vel *= std::pow(damp, t); // Aplicar amortiguamiento
	pos.p += (t * vel); // Calculo posicion i + 1
}