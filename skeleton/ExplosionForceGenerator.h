#pragma once

#include <cmath>

#include "ForceGenerator.h"

class ExplosionForceGenerator : public ForceGenerator {
public:
    ExplosionForceGenerator(const Vector3& center, double K, double R, double tau)
        : center(center), K(K), R(R), tau(tau) {
    }

    void trigger() { time = 0.0; active = true; }   // 

    void updateForce(double dt) override {
        if (!active) return;
        time += dt;
        if (time > 4.0 * tau) { active = false; return; }   // ya se ha desvanecido

        for (Particle* p : particles) {
            Vector3 d = p->getPosition() - center; // distancia desde el centro de la explosion a la particula
			double r = d.magnitude(); // distancia como magnitud
			if (r < R && r > 0) // si esta dentro del radio de la explosion y no esta en el centro
                p->addForce(d * (K / (r * r)) * std::exp(-time / tau));
        }
    }

private:
    Vector3 center;
    double K, R, tau;
    double time = 0.0;      // tiempo desde que se disparó la explosión
    bool active = false;
};
