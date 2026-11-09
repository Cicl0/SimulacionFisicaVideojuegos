#include "ExplosionForceGenerator.h"

void 
ExplosionForceGenerator::updateForce(const std::vector<Particle*>& particles, double dt) {
    if (!active) return;

    time += dt;
    if (time > 4.0 * tau) { active = false; return; }   // ya se ha desvanecido

    double intensity = K * std::exp(-time / tau);       // común a todas: se calcula una vez

    for (Particle* p : particles) {
        Vector3 d = p->getPosition() - center;
        double r = d.magnitude();
        if (r < R && r > 1e-6)
            p->addForce(d * (float)(intensity / (r * r)));
    }
}
