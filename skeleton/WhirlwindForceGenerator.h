#pragma once

#include "WindForceGenerator.h"

class WhirlwindForceGenerator : public WindForceGenerator {
public:
    WhirlwindForceGenerator(const Vector3& center, double radius, double om, double li, double he, double k1, double k2 = 0.0) :
        WindForceGenerator(Vector3(0.0f), center, radius, k1, k2),
		omega(om),
		lift(li),
        height(he)
    { }

    void setOmega(double o) { omega = o; }
    void setLift(double l) { lift = l; }
    void setHeight(double h) { height = h; }

    const char* name() const override { return "Torbellino"; }

    void drawUI() override {
        // El torbellino no usa windVelocity, así que dibujamos los campos comunes a mano
        ImGui::Checkbox("Activo", &active);
        ImGui::DragFloat3("Centro", &center.x, 1.0f);
        ImGui::DragScalar("Radio", ImGuiDataType_Double, &radius, 0.5f);
        ImGui::DragScalar("k1", ImGuiDataType_Double, &k1, 0.01f);
        ImGui::DragScalar("k2", ImGuiDataType_Double, &k2, 0.001f);

        ImGui::SeparatorText("Torbellino");
        ImGui::DragScalar("Omega (rad/s)", ImGuiDataType_Double, &omega, 0.1f);
        ImGui::Text("= %.2f vueltas/s", omega / (2.0 * 3.14159265));
        ImGui::DragScalar("Lift (m/s)", ImGuiDataType_Double, &lift, 0.5f);
        ImGui::DragScalar("Altura (m)", ImGuiDataType_Double, &height, 1.0f);
    }

protected:
    Vector3 windVelocityAt(const Vector3& pos) const override {
        Vector3 d = pos - center;
        return Vector3(static_cast<float>(-omega * d.z),
            static_cast<float>(lift * (1.0 - d.y / height)),
            static_cast<float>(omega * d.x));
    }

private:
    double omega;   // velocidad angular del viento (rad/s): vueltas/s = omega / (2*pi)
    double lift;    // velocidad vertical del viento en el centro (m/s)
    double height;  // altura donde el viento vertical se anula (m)
};

