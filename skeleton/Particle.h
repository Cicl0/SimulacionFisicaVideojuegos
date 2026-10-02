#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float Mass);
	~Particle();

	void integrate(double t);

private:
	Vector3 vel; // Velocidad
	Vector3 acc; // Aceleración
	physx::PxTransform pos; // Posición Y Rotacion
	RenderItem* renderItem; // Rederer
	float mass; // Masa
};

