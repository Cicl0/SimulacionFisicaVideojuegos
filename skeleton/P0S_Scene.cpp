#include "P0S_Scene.h"

#include <PxPhysicsAPI.h>

using namespace physx;

void P0S_Scene::init() {
	generator = new Generator(0.01f, 0.0f, 0.001f,		// Intervalo de generación, media y desviación de la velocidad
		Vector3(0.0f, 0.0f, 0.0f), 0.01f, 0.1f, 0.1f, 	// Dirección y desviación de la dirección
		-1.0f, 0.01f, 									// Media y desviación de la vida de la partícula
		Vector3(0.0f, 1.0f, 0.0f), 6.0f, 6.0f, 6.0f, 	// Origen y desviación de la posición
		10.0f, 0.97f,									// Masa y amortiguamiento
		Vector3(0.0f), 0.01f, 0.01f, 0.01f,				// Aceleración y desviación de la aceleración
		50);											// Número de partículas a generar

	explosionForceGenerator = new ExplosionForceGenerator(Vector3(0.0f, 0.0f, 0.0f), 30000.0f, 1000.0f, 1.0f);
	generator->addForceGenerator(explosionForceGenerator);
	gravityForceGenerator = new GravityForceGenerator(GRAVITY * 4);
	generator->addForceGenerator(gravityForceGenerator);
}

void
 P0S_Scene::update(double dt) {
	for (auto bullet : bullets) {
		bullet->integrate(dt);
	}
	generator->integrate(dt);

	explosionForceGenerator->updateForce(dt);
	gravityForceGenerator->updateForce(dt);
}

void P0S_Scene::cleanup() {
	if (m_renderItem) {
		m_renderItem->release(); // Deregistra y destruye el item
		m_renderItem = nullptr;
	}

	for (auto bullet : bullets) {
		delete bullet;
	}
}

void P0S_Scene::keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {
	if (key == 'k') {
		Bullet* bull = new Bullet(cameraTransform.p, // Posición inicial de la bala
								GetCamera()->getDir() * simulatedSpeed, // Velocidad Simulada
								Vector3(0.0f), // Aceleracion inicial de la bala
								0.8f, // Masa simulada de la bala
								1.0f, // Coeficiente de amortiguamiento
								GetCamera()->getDir() * 350.0f, 0.008f); // Velocidad y masa real
		bullets.push_back(bull);
	}
	if (key == 'u') {
		simulatedSpeed += 10.0f;
	}
	if (key == 'j') {
		simulatedSpeed -= 10.0f;
	}
	if (key == 'e') {
		explosionForceGenerator->trigger();
		gravityForceGenerator->triggerGravity();
	}
	if (key == 'g') {
		generator->triggerSpawn();
	}
}