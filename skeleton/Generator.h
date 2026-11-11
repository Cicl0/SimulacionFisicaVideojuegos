#pragma once

#include "Particle.h"

# include <random>

class ForceRegistry;

class Generator
{
public:
	Generator(const Particle& base,
		float inter,												// Intervalo de generación
		float velVarX, float velVarY, float velVarZ,				// Desviación de la velocidad
		float liveDev,												// Desviación de la vida
		float varX, float varY, float varZ,							// Desviación de la posición
		float accVarX, float accVarY, float accVarZ,				// Desviación de la aceleración
		int maxPart);												// Máximo de partículas vivas a la vez (-1 = sin límite)
	~Generator();

	void integrate(double t);

	void generate();

	const std::vector<Particle*>& getParticles() const { return particles; }

	// --- Getters y setters --- (principalmente para la UI)
	const int getMaxParticles() const { return maxParticles; }

	const int getAliveParticles() const { return aliveParticles; }

	bool isSpawning() const { return spawn; }

	void triggerSpawn() { spawn = !spawn; }

	float getInterval() const { return interval; }
	void setInterval(float i) { interval = (i > 0.001f) ? i : 0.001f; }

	float getLifeMean() const { return liveMean; }
	void setLifeMean(float l) { liveMean = (l > 0.1f) ? l : 0.1f; }

private:
	std::default_random_engine gen;
	std::normal_distribution<float> normal;

	// Valores medios (copiados de la partícula base) y desviaciones
	Vector3 origin, posDev;
	Vector3 velocity, velDev;
	Vector3 acceleration, accDev;
	float liveMean, liveDev;
	float mass, damp;
	Vector4 color;

	std::vector<Particle*> particles;
	int maxParticles;
	int aliveParticles = 0;

	float interval;
	float timeSinceLastGeneration = 0.0f;

	bool spawn = true;
};

