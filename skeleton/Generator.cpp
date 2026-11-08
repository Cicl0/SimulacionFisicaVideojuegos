#include "Generator.h"

#include <algorithm>
#include <iostream>

void 
Generator::integrate(double t) {
	if(timeSinceLastGeneration >= interval) {
		generate();
		timeSinceLastGeneration = 0.0f;
	} else {
		timeSinceLastGeneration += t;
	}

	for (auto& p : particles)
		p->integrate(t);

	for (auto it = particles.begin(); it != particles.end(); ) {
		if (!(*it)->isAlive()) {
			// 1. quitarla de todos los generadores de fuerzas
			for (ForceGenerator* fg : forceGenerators)
				fg->removeParticle(*it);

			// 2. liberar la memoria
			delete* it;

			// 3. quitarla del vector 
			it = particles.erase(it);
		}
		else
			++it;
	}
}

void 
Generator::generate()
{
	if (!spawn) return;

	// Límite de partículas alcanzado (-1 = sin límite)
	if (numParticles != -1 && particles.size() >= static_cast<size_t>(numParticles)) return;

	Vector3 pos(position_dist_X(generator), // 1. genero la posicion
		position_dist_Y(generator),
		position_dist_Z(generator));

	Vector3 dir(direction_dist_X(generator), // 2. genero la direccion
		direction_dist_Y(generator),
		direction_dist_Z(generator));

	Vector3 acc(acceleration_dist_X(generator), // 3. genero la acceleracion
		acceleration_dist_Y(generator),
		acceleration_dist_Z(generator));

	float speed = (std::max)(0.0f, velocity_dist(generator)); // 4. aplico velocidad
	float life = lifetime_dist(generator); // 5. aplico tiempo de vida

	Particle* p = new Particle(pos, dir * speed, acc, mass, damp, life);
	particles.push_back(p);

	// 6. Suscribir la nueva partícula a todos los generadores de fuerzas
	for (ForceGenerator* fg : forceGenerators)
		fg->addParticle(p);
}