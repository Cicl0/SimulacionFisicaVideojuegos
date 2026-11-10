#pragma once

#include "Particle.h"
#include <imgui.h>

class ForceGenerator
{
public:
	ForceGenerator() = default;

	virtual void updateForce(const std::vector<Particle*>& particles, double dt) = 0;

	virtual const char* name() const = 0;
	virtual void drawUI() {}

protected:
	std::vector<Particle*> particles;
};