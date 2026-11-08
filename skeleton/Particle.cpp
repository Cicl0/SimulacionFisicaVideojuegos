#include "Particle.h"
#include <cmath> 

Particle::Particle(Vector3 p = { 0.0f, 0.0f, 0.0f }, Vector3 v = {0.0f, 0.0f, 0.0f}, Vector3 a = {0.0f, 0.0f, 0.0f}, float m = 0, float d = 0, float lt = -1.0f) :
	pos(p),
	vel(v),
	acc(a),
	mass(m),
	lifetime(lt),
	age(0.0f)
{
	if (d > 1) damp = 1;
	else if (d < 0) damp = 0;
	else damp = d;

	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
	renderItem = new RenderItem(shape, &pos, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
}

void Particle::integrate(double t) {
	// a = a_propia + F/m
	Vector3 totalAcc = acc + force * getInverseMass();

	vel += t * totalAcc; // Calculo velocidad i + 1
	vel *= std::pow(damp, t); // Aplicar amortiguamiento
	pos.p += (t * vel); // Calculo posicion i + 1

	clearForce(); // importante: vaciar el acumulador cada frame

	if(lifetime > 0) {
		age += t;
		if (age >= lifetime) {
			alive = false;
		}
	}
}