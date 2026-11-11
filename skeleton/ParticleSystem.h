#pragma once

#include "Generator.h"

class Generator;
class ParticleSystem
{
public:
	ParticleSystem() {}
	
	void addGenerator(Generator* generator) { generators.push_back(generator); }

	std::vector<Generator*> getGenerators() const { return generators; }

	void integrate(double dt) {
		for (auto& generator : generators) {
			generator->integrate(dt);
		}
	}

	void clear() { generators.clear(); }

	std::vector<Particle*> getAllParticles() const {
		std::vector<Particle*> allParticles;
		for (const auto& generator : generators) {
			const auto& particles = generator->getParticles();
			allParticles.insert(allParticles.end(), particles.begin(), particles.end());
		}
		return allParticles;
	}
private:
	std::vector<Generator*> generators;
};

