#pragma once

#include <cmath>
#include "ForceGenerator.h"

class WindForceGenerator : public ForceGenerator {
public:
    WindForceGenerator(const Vector3& windVel, const Vector3& center, double radius, float k1, float k2 = 0.0) :
        windVelocity(windVel),
        center(center),
        radius(radius),
        k1(k1),
        k2(k2) 
    { }

    void updateForce(const std::vector<Particle*>& particles, double dt) override {
        for (Particle* p : particles) {
            Vector3 pos = p->getPosition();
            if (!isInside(pos)) continue;

            Vector3 vw = windVelocityAt(pos);
            Vector3 rel = vw - p->getVelocity();

            Vector3 F = rel * static_cast<float>(k1) + rel * static_cast<float>(k2 * rel.magnitude());
            p->addForce(F);
        }
    }

    // Tarea opcional: k2 = Aeff * CD * rho (para una esfera CD = 0.5, aire rho ~ 1.2 kg/m^3)
    void setQuadraticFromShape(double Aeff, double Cd, double rho) { k2 = Aeff * Cd * rho; }

    void setWindVelocity(const Vector3& v) { windVelocity = v; }
    void setK1(double v) { k1 = v; }
    void setK2(double v) { k2 = v; }

protected:
    // Zona de influencia: esfera de centro 'center' y radio 'radius'
    virtual bool isInside(const Vector3& pos) const {
        return (pos - center).magnitude() < radius;
    }

    // Viento uniforme: igual en todo el volumen. Las clases hijas lo sobreescriben.
    virtual Vector3 windVelocityAt(const Vector3& pos) const { return windVelocity; }

    Vector3 windVelocity;
    Vector3 center;
    double radius;
    double k1, k2;
};

