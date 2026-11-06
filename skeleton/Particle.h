#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"

const Vector3 GRAVITY = Vector3(0.0f, -9.80665f, 0.0f); // He tomado como gravedad general la gravedad estándar de la Tierra en m/s²

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float Mass, float Damp, float Lifetime);
	~Particle() {}

	virtual void init() {}

	virtual void integrate(double t);

	virtual void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {}

	bool isAlive() const { return alive; }

	// gravity = (Vsm2 * Gr) / Vr2

protected:
	Vector3 vel; // Velocidad
	Vector3 acc; // Aceleración
	physx::PxTransform pos; // Posición Y Rotacion
	RenderItem* renderItem; // Rederer
	float mass; // Masa
	float damp;
	Vector3 gravity;

	float lifetime; // Tiempo de vida de la particula
	float age; // Edad de la particula
	bool alive = true; // Estado de la particula
};

