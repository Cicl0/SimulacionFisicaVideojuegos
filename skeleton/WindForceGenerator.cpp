#include "WindForceGenerator.h"

void 
WindForceGenerator::updateForce(const std::vector<Particle*>& particles, double dt) {
    for (Particle* p : particles) {
        Vector3 pos = p->getPosition();
        if (!isInside(pos)) continue;

        Vector3 vw = windVelocityAt(pos);
        Vector3 rel = vw - p->getVelocity();

        Vector3 F = rel * (float)(k1)+rel * (float)(k2 * rel.magnitude());
        p->addForce(F);
    }
}