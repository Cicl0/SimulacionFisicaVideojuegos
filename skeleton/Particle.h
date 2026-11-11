#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"

const Vector3 GRAVITY = Vector3(0.0f, -9.80665f, 0.0f); // He tomado como gravedad general la gravedad estándar de la Tierra en m/s²

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float Mass, float Damp, float Lifetime, Vector4 color = { 1.0f, 0.0f, 0.0f, 1.0f });
	~Particle();

	virtual void init() {}

	virtual void integrate(double t);

	virtual void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {}

	// Devuelve si la particula esta viva o muerta
	bool isAlive() const { return alive; }

	// --- Fuerzas ---
	// Acumula una fuerza (en N) que se aplicará en el próximo integrate().
	void addForce(const Vector3& f) { force += f; }

	// Pone a cero el acumulador (se llama al final de integrate()).
	void clearForce() { force = Vector3(0.0f, 0.0f, 0.0f); }

	// --- Getters que usan los generadores ---
	float getMass() const { return mass; }
	float getInverseMass() const { return (mass > 0.0f) ? 1.0f / mass : 0.0f; }

	Vector3 getAcceleration() const { return acc; }
	Vector3 getVelocity() const { return vel; }
	Vector3 getPosition() const { return pos.p; }

	float getDamp() const { return damp; }

	float getLifetime() const { return lifetime; }
	Vector4 getColor() const { return renderItem->color; }

protected:
	Vector3 vel; // Velocidad
	Vector3 acc; // Aceleración
	physx::PxTransform pos; // Posición Y Rotacion

	RenderItem* renderItem; // Rederer

	float mass; // Masa
	float damp;

	Vector3 force = Vector3(0.0f, 0.0f, 0.0f); // Fuerza acumulada en este frame

	float lifetime; // Tiempo de vida de la particula
	float age; // Edad de la particula
	bool alive = true; // Estado de la particula
};

