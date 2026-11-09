#include "Generator.h"

#include <algorithm>
#include <iostream>

Generator::Generator(float inter, float velMed, float velDev, // Intervalo de generación, media y desviación de la velocidad
	Vector3 dir, float dirVarX, float dirVarY, float dirVarZ, // Dirección y desviación de la dirección
	float liveMed, float liveDev,							  // Media y desviación de la vida de la partícula
	Vector3 origin, float varX, float varY, float varZ,       // Origen y desviación de la posición
	float m, float d,										  // Masa y amortiguamiento
	Vector3 acc, float accVarX, float accVarY, float accVarZ, // Aceleración y desviación de la aceleración
	int numPart)											  // Maximo de particulas a generar (-1 = sin limite)
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

void 
Generator::integrate(double t) {
	// Generar nuevas partículas si ha pasado el intervalo de tiempo
	if(timeSinceLastGeneration >= interval) {
		generate();
		timeSinceLastGeneration = 0.0f;
	} else {
		timeSinceLastGeneration += t;
	}

	// Actualizar todas las partículas
	for (auto& p : particles)
		p->integrate(t);

	// Eliminar partículas muertas
	for (auto it = particles.begin(); it != particles.end(); ) {
		if (!(*it)->isAlive()) {
			delete* it;
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
	if (numParticles != -1 && particles.size() >= numParticles) return;

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
}