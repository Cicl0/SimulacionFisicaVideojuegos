#pragma once

#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator() = default;

	virtual void updateForce(const std::vector<Particle*>& particles, double dt) = 0;

protected:
	std::vector<Particle*> particles;
};