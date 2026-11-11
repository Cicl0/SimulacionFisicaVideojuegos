#pragma once

#include <cmath>

#include "ForceGenerator.h"

class ExplosionForceGenerator : public ForceGenerator {
public:
    ExplosionForceGenerator(const Vector3& center, double k, double r, double t)
        : center(center), K(k), R(r), tau(t) {
    }

    void trigger() { time = 0.0; active = true; }   // 

    void updateForce(const std::vector<Particle*>& particles, double dt) override;

    const char* name() const override { return "Explosion"; }

    void drawUI() override {
        ImGui::DragFloat3("Centro", &center.x, 1.0f);
        ImGui::DragScalar("K (intensidad)", ImGuiDataType_Double, &K, 100.0f);
        ImGui::DragScalar("R (radio)", ImGuiDataType_Double, &R, 1.0f, nullptr, nullptr);
        ImGui::DragScalar("tau", ImGuiDataType_Double, &tau, 0.01f);

        ImGui::Separator();
        ImGui::Text("Estado: %s  (t = %.2f s)", active ? "ACTIVA" : "inactiva", time);
        if (ImGui::Button("Disparar")) trigger();
    }
private:
    Vector3 center;
    double K, R, tau;
    double time = 0.0;      // tiempo desde que se disparó la explosión
    bool active = false;
};
