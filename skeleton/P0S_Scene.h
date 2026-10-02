#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"

class P0S_Scene : public Scene
{
public:
	explicit P0S_Scene(std::string name) : Scene(std::move(name)) {}

	void init() override;

	void update(double dt) override {
		// Lógica/Integración del alumno (por ejemplo, movimiento simple)
		//m_transform.p.y -= static_cast<float>(9.8 * dt);
	}

	void cleanup() override;

	void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) override;

private:
	physx::PxTransform m_transform;
	RenderItem* m_renderItem{ nullptr };
};

