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
		Vector3 acc, float accVarX, float accVarY, float accVarZ,
		int numPart) // Aceleración y desviación de la aceleración
		:
		generator(std::random_device{}()),
		direction(dir.getNormalized()),
		mass(m),
		damp(d),
		numParticles(numPart),
		interval(inter),
		timeSinceLastGeneration(0.0f)
	{
		// Inicializamos las distribuciones normales para cada parámetro
		lifetime_dist = std::normal_distribution<float>(liveMed, liveDev);
		velocity_dist = std::normal_distribution<float>(velMed, velDev);

		// Inicializamos las distribuciones normales para la dirección, aceleración y posición
		direction_dist_X = std::normal_distribution<float>(dir.x, dirVarX);
		direction_dist_Y = std::normal_distribution<float>(dir.y, dirVarY);
		direction_dist_Z = std::normal_distribution<float>(dir.z, dirVarZ);

		// Inicializamos las distribuciones normales para la aceleración
		acceleration_dist_X = std::normal_distribution<float>(acc.x, accVarX);
		acceleration_dist_Y = std::normal_distribution<float>(acc.y, accVarY);
		acceleration_dist_Z = std::normal_distribution<float>(acc.z, accVarZ);

		// Inicializamos las distribuciones normales para la posición
		position_dist_X = std::normal_distribution<float>(origin.x, varX);
		position_dist_Y = std::normal_distribution<float>(origin.y, varY);
		position_dist_Z = std::normal_distribution<float>(origin.z, varZ);

		// Si numParticles es -1, no hay límite de partículas, así que no reservamos espacio inicialmente
		particles.reserve(numParticles == -1 ? 0 : numParticles);
	}

	void integrate(double t);

	void generate();

	void addForceGenerator(ForceGenerator* fg) {
		if (!fg) return;

		// Evitar duplicados
		if (std::find(forceGenerators.begin(), forceGenerators.end(), fg) != forceGenerators.end())
			return;

		forceGenerators.push_back(fg);

		// Suscribir las partículas que ya existen
		for (Particle* p : particles)
			fg->addParticle(p);
	}

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
	ForceRegistry* forces;
	std::vector<ForceGenerator*> forceGenerators;
	int numParticles;

	float interval;
	float timeSinceLastGeneration = 0.0f;

	bool spawn = true;
};

