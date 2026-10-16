#include "P0S_Scene.h"

#include <PxPhysicsAPI.h>

using namespace physx;

void P0S_Scene::init() {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
	m_transform = physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f));

	m_renderItem = new RenderItem(shape, &m_transform, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
}

void
 P0S_Scene::update(double dt) {
	for (auto bullet : bullets) {
		bullet->integrate(dt);
	}
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
}