#pragma once

#include "Particle.h"

# include <random>

class Generator
{
public:
	Generator(float inter, float velMed, float velDev, 
		Vector3 dir, float dirVarX, float dirVarY, float dirVarZ,
		float liveMed, float liveDev, Vector3 origin,
		float varX, float varY, float varZ, float m, float d, Vector3 grav) :
		interval(inter),
		timeSinceLastGeneration(0.0f),
		direction(dir.getNormalized()),
		generator(std::random_device{}()),
		mass(m),
		damp(d),
		gravity(grav)
	{
		lifetime_dist = std::normal_distribution<float>(liveMed, liveDev);
		velocity_dist = std::normal_distribution<float>(velMed, velDev);

		direction_dist_X = std::normal_distribution<float>(dir.x, dirVarX);
		direction_dist_Y = std::normal_distribution<float>(dir.y, dirVarY);
		direction_dist_Z = std::normal_distribution<float>(dir.z, dirVarZ);

		position_dist_X = std::normal_distribution<float>(origin.x, varX);
		position_dist_Y = std::normal_distribution<float>(origin.y, varY);
		position_dist_Z = std::normal_distribution<float>(origin.z, varZ);
	}

	void integrate(double t);

	void generate();

	const std::vector<std::unique_ptr<Particle>>& getParticles() const { return particles; }

private:
	std::default_random_engine generator;
	std::normal_distribution<float> lifetime_dist;
	std::normal_distribution<float> velocity_dist;
	std::normal_distribution<float> direction_dist_X;
	std::normal_distribution<float> direction_dist_Y;
	std::normal_distribution<float> direction_dist_Z;

	std::normal_distribution<float> position_dist_X;
	std::normal_distribution<float> position_dist_Y;
	std::normal_distribution<float> position_dist_Z;

	Vector3 direction;

	float mass, damp;

	std::vector<std::unique_ptr<Particle>> particles;

	float interval;
	float timeSinceLastGeneration = 0.0f;

	Vector3 gravity;
};

