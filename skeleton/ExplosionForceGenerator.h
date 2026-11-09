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

private:
    Vector3 center;
    double K, R, tau;
    double time = 0.0;      // tiempo desde que se disparó la explosión
    bool active = false;
};
