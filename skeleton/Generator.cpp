#include "Generator.h"

#include <algorithm>
#include <iostream>

void 
Generator::integrate(double t) {
	if(timeSinceLastGeneration >= interval) {
		generate();
		timeSinceLastGeneration = 0.0f;
		std::cout << "Generada" << std::endl;
	} else {
		timeSinceLastGeneration += t;
	}

	for (auto& p : particles)
		p->integrate(t);

	for (auto it = particles.begin(); it != particles.end(); ) {
		if (!(*it)->isAlive())
			it = particles.erase(it);   
		else
			++it;
	}
}

void 
Generator::generate()
{
	particles.reserve(particles.size() + 1);
	
	Vector3 pos(position_dist_X(generator),
		position_dist_Y(generator),
		position_dist_Z(generator));

	Vector3 dir(direction_dist_X(generator),
		direction_dist_Y(generator),
		direction_dist_Z(generator));

	Vector3 acc(acceleration_dist_X(generator),
		acceleration_dist_Y(generator),
		acceleration_dist_Z(generator));

	float speed = (std::max)(0.0f, velocity_dist(generator));
	float life = (std::max)(0.01f, lifetime_dist(generator));

	particles.push_back(std::make_unique<Particle>(
		pos, dir * speed, gravity + acc, mass, damp, life));
}