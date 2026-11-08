#pragma once

#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator() = default;

	virtual void updateForce(double dt) = 0;

	void addParticle(Particle* p) { particles.push_back(p); }

	void removeParticle(Particle* p) {
		particles.erase(std::remove(particles.begin(), particles.end(), p), particles.end());
	}

protected:
	std::vector<Particle*> particles;
};