#pragma once

#include "ForceGenerator.h"


class GravityForceGenerator : public ForceGenerator {
public:
    explicit GravityForceGenerator(const Vector3& g = {0.0f, -9.81, 0.0f}) : gravity(g) {}

    void updateForce(double dt) override {
		if (!active) return;
        for (Particle* p : particles)
            p->addForce(gravity * p->getMass());
    }

    void triggerGravity() { active = !active; }

private:
    Vector3 gravity;
	bool active = false;
};
