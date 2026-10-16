#pragma once

#include "Particle.h"

class Bullet : public Particle
{
public:
	Bullet(Vector3 Pos, Vector3 Vel, Vector3 Acc, float Mass, float Damp, Vector3 VelReal, float MassReal) : 
		Particle(Pos, Vel, Acc, Mass, Damp),
		velR(VelReal),
		velS(Vel),
		massR(MassReal)
	{
		init();
	}
	~Bullet() {}

	void init() override;

	void integrate(double t) override;

	void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) override;

	void simulateMass();

	void simulateGravity();

protected:
	Vector3 velR;
	Vector3 velS;
	float massR;
};

