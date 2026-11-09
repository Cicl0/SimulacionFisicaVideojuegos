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

    void updateForce(const std::vector<Particle*>& particles, double dt) override;

    // Tarea opcional: k2 = Aeff * CD * rho (para una esfera CD = 0.5, aire rho ~ 1.2 kg/m^3)
	// aeff = area efectiva de la particula (en esferas pi*r2)
	// cd = coeficiente de arrastre, drag coefficient
	// airDen = densidad del aire, kg/m^3 (densidad del aire ~1,2 kg/m^3)

    void setQuadraticFromShape(double aeff, double cd, double airDen) { k2 = aeff * cd * airDen; }

    void setWindVelocity(const Vector3& v) { windVelocity = v; }
    void setK1(double v) { k1 = v; }
    void setK2(double v) { k2 = v; }

protected:
    // Zona de influencia: esfera de centro 'center' y radio 'radius'
    virtual bool isInside(const Vector3& pos) const { return (pos - center).magnitude() < radius; }

    // Viento uniforme: igual en todo el volumen. Las clases hijas lo sobreescriben.
    virtual Vector3 windVelocityAt(const Vector3& pos) const { return windVelocity; }

    Vector3 windVelocity;
    Vector3 center;
    double radius;
    double k1, k2;
};

