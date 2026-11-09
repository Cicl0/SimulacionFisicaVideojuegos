#pragma once

#include "Particle.h"
#include "ForceGenerator.h"
#include "ForceRegistry.h"

# include <random>

class ForceRegistry;

class Generator
{
public:
	Generator(float inter, float velMed, float velDev,			  // Intervalo de generación, media y desviación de la velocidad
		Vector3 dir, float dirVarX, float dirVarY, float dirVarZ, // Dirección y desviación de la dirección
		float liveMed, float liveDev,							  // Media y desviación de la vida de la partícula
		Vector3 origin, float varX, float varY, float varZ,       // Origen y desviación de la posición
		float m, float d,										  // Masa y amortiguamiento
		Vector3 acc, float accVarX, float accVarY, float accVarZ, // Aceleración y desviación de la aceleración
		int numPart);											  // Maximo de particulas a generar (-1 = sin limite)

	void integrate(double t);

	void generate();

	const std::vector<Particle*>& getParticles() const { return particles; }

	void triggerSpawn() { spawn = !spawn; }

private:
	std::default_random_engine generator;
	std::normal_distribution<float> lifetime_dist;
	std::normal_distribution<float> velocity_dist;

	std::normal_distribution<float> direction_dist_X;
	std::normal_distribution<float> direction_dist_Y;
	std::normal_distribution<float> direction_dist_Z;

	std::normal_distribution<float> acceleration_dist_X;
	std::normal_distribution<float> acceleration_dist_Y;
	std::normal_distribution<float> acceleration_dist_Z;

	std::normal_distribution<float> position_dist_X;
	std::normal_distribution<float> position_dist_Y;
	std::normal_distribution<float> position_dist_Z;

	Vector3 direction;

	float mass, damp;

	std::vector<Particle*> particles;
	int numParticles;

	float interval;
	float timeSinceLastGeneration = 0.0f;

	bool spawn = true;
};

