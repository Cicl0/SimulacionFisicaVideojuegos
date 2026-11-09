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

