#include "Generator.h"

#include <algorithm>
#include <cmath>
#include <iostream>

Generator::Generator(const Particle& base,
	float inter,												// Intervalo de generación
	float velVarX, float velVarY, float velVarZ,				// Desviación de la velocidad
	float liveDv,												// Desviación de la vida
	float varX, float varY, float varZ,							// Desviación de la posición
	float accVarX, float accVarY, float accVarZ,				// Desviación de la aceleración
	int maxPart)												// Máximo de partículas vivas a la vez (-1 = sin límite)
	:
	gen(std::random_device{}()),
	normal(0.0f, 1.0f),
	origin(base.getPosition()), posDev(varX, varY, varZ),
	velocity(base.getVelocity()), velDev(velVarX, velVarY, velVarZ),
	acceleration(base.getAcceleration()), accDev(accVarX, accVarY, accVarZ),
	liveMean(base.getLifetime()), liveDev(liveDv),
	mass(base.getMass()), damp(base.getDamp()),
	color(base.getColor()),
	maxParticles(maxPart),
	interval(inter)
{
	// Si numParticles es -1, no hay límite de partículas, así que no reservamos espacio inicialmente
	particles.reserve(maxParticles == -1 ? 0 : maxParticles);
}

Generator::~Generator()
{
	for (Particle* p : particles)
		delete p;
}

void 
Generator::integrate(double t) {
	// Generación por intervalo
	if (spawn && interval > 0.0f) {
		timeSinceLastGeneration += (float)t;

		// while por si el frame es largo y toca generar varias a la vez
		while (timeSinceLastGeneration >= interval) {
			timeSinceLastGeneration -= interval;

			if (maxParticles >= 0 && (int)particles.size() >= maxParticles) {
				timeSinceLastGeneration = 0.0f;
				break;
			}
			generate();
		}
	}

	// Actualizar y eliminar las muertas en un solo recorrido
	particles.erase(std::remove_if(particles.begin(), particles.end(),
		[t, this](Particle* p) {
			p->integrate(t);

			if (!p->isAlive()) {
				delete p;
				aliveParticles--;
				return true;
			}
			return false;
		}),
		particles.end());
}

void 
Generator::generate() {
	// Posición
	Vector3 pos = origin + Vector3(normal(gen) * posDev.x,
		normal(gen) * posDev.y,
		normal(gen) * posDev.z);

	// Velocidad
	Vector3 vel = velocity + Vector3(normal(gen) * velDev.x,
		normal(gen) * velDev.y,
		normal(gen) * velDev.z);

	// Aceleración
	Vector3 acc = acceleration + Vector3(normal(gen) * accDev.x,
		normal(gen) * accDev.y,
		normal(gen) * accDev.z);

	// Vida 
	float life = liveMean + normal(gen) * liveDev;

	Particle* p = new Particle(pos, vel, acc, mass, damp, life, color);
	particles.push_back(p);
	aliveParticles++;
}