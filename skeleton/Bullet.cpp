#include "Bullet.h"

#include <cmath>
#include <iostream>

void Bullet::integrate(double t) {
	vel += t * (acc); // Calculo velocidad i + 1
	vel *= std::pow(damp, t); // Aplicar amortiguamiento
	simulateGravity(); // Simular gravedad
	simulateMass(); // Simular masa
	vel += t * (gravity);
	pos.p += (t * vel); // Calculo posicion i + 1
	if (pos.p.y > 0) std::cout << "Bullet y acc: " << pos.p.x << std::endl; // Imprimir altura de la bala
}

void Bullet::keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {
	switch (key) {
	case 'u':
		mass++;
		break;
	case'j':
		mass--;
		break;
	}
}

void Bullet::simulateMass() {
	// mass = (massR * Vr2) / Vs2
	mass = massR * (velR.magnitudeSquared() / vel.magnitudeSquared());
}

void Bullet::simulateGravity() {
	// gravity = (Vsm2 * Gr) / Vr2
	gravity = GRAVITY * (vel.magnitudeSquared() / velR.magnitudeSquared());

}