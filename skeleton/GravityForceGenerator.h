#pragma once

#include "ForceGenerator.h"


class GravityForceGenerator : public ForceGenerator {
public:
    explicit GravityForceGenerator(const Vector3& g = {0.0f, -9.81, 0.0f}) : gravity(g) {}

    void updateForce(const std::vector<Particle*>& particles, double dt) override {
		if (!active) return;
        for (Particle* p : particles)
            p->addForce(gravity * p->getMass());
    }

    void triggerGravity() { active = !active; }

    const char* name() const override { return "Gravedad"; }

    void drawUI() override {
        ImGui::Checkbox("Activa", &active);
        ImGui::DragFloat3("Gravedad (m/s²)", &gravity.x, 0.1f);
        if (ImGui::Button("Reset (0,-9.81,0)")) gravity = Vector3(0.0f, -9.81f, 0.0f);
    }

private:
    Vector3 gravity;
	bool active = true;
};
