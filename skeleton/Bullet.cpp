#include "Bullet.h"

#include <cmath>
#include <iostream>

void
Bullet::init() {
	simulateMass();
	simulateGravity();
}

void 
Bullet::integrate(double t) {
	vel += t * (acc + gravity); // Calculo velocidad i + 1
	vel *= std::pow(damp, t); // Aplicar amortiguamiento
	pos.p += (t * vel); // Calculo posicion i + 1
}

void 
Bullet::keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {
}

void 
Bullet::simulateMass() {
	// mass = (massR * Vr2) / Vs2
	mass = massR * (velR.magnitudeSquared() / velS.magnitudeSquared());
}

void 
Bullet::simulateGravity() {
	// gravity = (Vsm2 * Gr) / Vr2
	
	gravity = GRAVITY * (velS.magnitudeSquared() / velR.magnitudeSquared());

}