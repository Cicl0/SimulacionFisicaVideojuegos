#include "P0S_Scene.h"

#include <PxPhysicsAPI.h>
#include <iostream>

using namespace physx;

void P0S_Scene::init() {
	forceRegistry = new ForceRegistry();

	explosionForceGenerator = forceRegistry->create<ExplosionForceGenerator>(Vector3(60.0f, 0.0f, 0.0f), 60000.0f, 1000.0f, 1.0f);
	fgList.push_back(explosionForceGenerator);

	gravityForceGenerator = forceRegistry->create<GravityForceGenerator>(GRAVITY * 8);
	fgList.push_back(gravityForceGenerator);

	windForceGenerator = forceRegistry->create<WindForceGenerator>(Vector3(0.0f, 0.0f, 700.0f), Vector3(0.0f, 0.0f, 0.0f), 20000.0f, 60.0f);
	fgList.push_back(windForceGenerator);

	whirlwindForceGenerator = forceRegistry->create<WhirlwindForceGenerator>(Vector3(180.0f, 0.0f, 0.0f), 30.0f, 5.0f, 150.0f, 300.0f, 100.0, 0.1);
	fgList.push_back(whirlwindForceGenerator);

	manguera = new ParticleSystem();

	Particle particle(Vector3(0.0f, 1.0f, 0.0f),	// Origen
		Vector3(0.0f, 80.0f, 0.0f),	// Velocidad (módulo 0)
		Vector3(0.0f),				// Aceleración
		10.0f, 0.97f,				// Masa y amortiguamiento
		1.5f,
		Vector4(0.0f, 0.0f, 1.0f, 1.0f));						// Vida

	// Chorro de agua
	generator = new Generator(particle,
		0.01f,							// Intervalo de generación
		3.0f, 0.001f, 3.0f,			// Desviación de la velocidad
		0.01f,							// Desviación de la vida
		1.0f, 1.0f, 1.0f,				// Desviación de la posición
		0.01f, 0.01f, 0.01f,			// Desviación de la aceleración
		5000);							// Máximo de partículas vivas

	bomba = new ParticleSystem();

	Particle particle2(Vector3(60.0f, 1.0f, 0.0f),	// Origen
		Vector3(0.0f, 0.0f, 0.0f),	// Velocidad (módulo 0)
		Vector3(0.0f),				// Aceleración
		10.0f, 0.97f,				// Masa y amortiguamiento
		1.5f,
		Vector4(1.0f, 0.0f, 0.0f, 1.0f));						// Vida

	// Explosion 
	Generator* generator_2 = new Generator(particle2,
		0.01f,							// Intervalo de generación
		0.001f, 0.001f, 0.001f,			// Desviación de la velocidad
		0.01f,							// Desviación de la vida
		6.0f, 6.0f, 6.0f,				// Desviación de la posición
		0.01f, 0.01f, 0.01f,			// Desviación de la aceleración
		5000);							// Máximo de partículas vivas

	viento = new ParticleSystem();

	Particle particle3(Vector3(120.0f, 1.0f, 0.0f),	// Origen
		Vector3(0.0f, 0.0f, 0.0f),	// Velocidad (módulo 0)
		Vector3(0.0f),				// Aceleración
		10.0f, 0.97f,				// Masa y amortiguamiento
		1.5f,
		Vector4(1.0f, 0.0f, 1.0f, 1.0f));						// Vida

	// Viento 
	Generator* generator_3 = new Generator(particle3,
		10.01f,							// Intervalo de generación
		0.001f, 0.001f, 0.001f,			// Desviación de la velocidad
		0.01f,							// Desviación de la vida
		6.0f, 6.0f, 6.0f,				// Desviación de la posición
		0.01f, 0.01f, 0.01f,			// Desviación de la aceleración
		5000);							// Máximo de partículas vivas

	torbellino = new ParticleSystem();

	Particle particle4(Vector3(180.0f, 1.0f, 0.0f),	// Origen
		Vector3(0.0f, 0.0f, 0.0f),	// Velocidad (módulo 0)
		Vector3(0.0f),				// Aceleración
		10.0f, 0.97f,				// Masa y amortiguamiento
		1.5f,
		Vector4(0.0f, 1.0f, 0.0f, 1.0f));						// Vida

	// Torbellino
	Generator* generator_4 = new Generator(particle4,
		0.01f,							// Intervalo de generación
		0.001f, 0.001f, 0.001f,			// Desviación de la velocidad
		0.01f,							// Desviación de la vida
		6.0f, 6.0f, 6.0f,				// Desviación de la posición
		0.01f, 0.01f, 0.01f,			// Desviación de la aceleración
		5000);							// Máximo de partículas vivas

	manguera->addGenerator(generator);
	bomba->addGenerator(generator_2);
	viento->addGenerator(generator_3);
	torbellino->addGenerator(generator_4);

	particleSystems.push_back(manguera);
	particleSystems.push_back(bomba);
	particleSystems.push_back(viento);
	particleSystems.push_back(torbellino);

	forceRegistry->bind(gravityForceGenerator, manguera);
	forceRegistry->bind(explosionForceGenerator, bomba);
	forceRegistry->bind(windForceGenerator, viento);
	forceRegistry->bind(whirlwindForceGenerator, torbellino);

	Snippets::setUICallback([this]() { drawUI(); });
}

void
 P0S_Scene::update(double dt) {
	for (auto bullet : bullets) {
		bullet->integrate(dt);
	}
	manguera->integrate(dt);
	bomba->integrate(dt);
	viento->integrate(dt);
	torbellino->integrate(dt);
	
	forceRegistry->updateForce(dt);
}

void P0S_Scene::cleanup() {
	Snippets::setUICallback(nullptr);

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
	if (key == 'i') {
		Bullet* bull = new Bullet(cameraTransform.p, // Posición inicial de la bala
			GetCamera()->getDir() * simulatedSpeed/2, // Velocidad Simulada
			Vector3(0.0f), // Aceleracion inicial de la bala
			10.0f, // Masa simulada de la bala
			0.9f, // Coeficiente de amortiguamiento
			GetCamera()->getDir() * 50.0f, 0.008f); // Velocidad y masa real
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
	}
	if (key == 'g') {
		gravityForceGenerator->triggerGravity();
	}
	if (key == 'r') {
		windForceGenerator->triggerWind();
	}
	if (key == 'f') {
		whirlwindForceGenerator->triggerWind(); // Como hereda de wind, tambien hereda su forma de desactivarse/activarse
	}
	if (key == 't') {
		generator->triggerSpawn();
	}
}

void 
P0S_Scene::drawUI() {
	const ImGuiViewport* vp = ImGui::GetMainViewport();

	// Anclado al lado derecho; cambia a vp->WorkPos.x para el izquierdo
	float w = vp->WorkSize.x * 0.25f;
	ImGui::SetNextWindowPos(ImVec2(vp->WorkPos.x + vp->WorkSize.x - w, vp->WorkPos.y));
	ImGui::SetNextWindowSize(ImVec2(w, vp->WorkSize.y));

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoCollapse;

	ImGui::Begin("Debug", nullptr, flags);

	if (ImGui::BeginTabBar("DebugTabs")) {

		if (ImGui::BeginTabItem("Fuerzas")) {
			// Sub-pestañas o secciones plegables por generador
			for (auto* fg : fgList) {
				ImGui::PushID(fg);
				if (ImGui::CollapsingHeader(fg->name(), ImGuiTreeNodeFlags_DefaultOpen))
					fg->drawUI();
				ImGui::PopID();
			}
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Generadores")) {
			for (size_t j = 0; j < particleSystems.size(); ++j) {
				auto& ps = particleSystems[j];
				auto& generators = ps->getGenerators();

				ImGui::PushID((int)j);   // ID único por sistema de partículas

				std::string sysTitle = "Sistema " + std::to_string(j);
				if (ImGui::CollapsingHeader(sysTitle.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {

					for (size_t i = 0; i < generators.size(); ++i) {
						Generator* gen = generators[i];

						ImGui::PushID((int)i);   // ID único por generador dentro del sistema

						std::string title = "Generador " + std::to_string(i);
						if (ImGui::TreeNodeEx(title.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {

							bool spawning = gen->isSpawning();
							if (ImGui::Checkbox("Activo", &spawning))
								gen->triggerSpawn();

							ImGui::Text("Partículas: %d", gen->getMaxParticles());
							ImGui::Text("Partículas vivas: %d", gen->getAliveParticles());

							// Intervalo entre generaciones
							float interval = gen->getInterval();
							if (ImGui::SliderFloat("Intervalo (s)", &interval, 0.001f, 1.0f, "%.3f", ImGuiSliderFlags_Logarithmic))
								gen->setInterval(interval);

							// Vida media de las partículas nuevas
							float life = gen->getLifeMean();
							if (ImGui::SliderFloat("Vida media (s)", &life, 0.1f, 20.0f, "%.2f"))
								gen->setLifeMean(life);

							ImGui::TreePop();
						}

						ImGui::PopID();
					}
				}

				ImGui::PopID();
			}

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Balas")) {
			ImGui::DragFloat("Velocidad simulada", &simulatedSpeed, 1.0f, 0.0f, 1000.0f);
			ImGui::Text("Balas activas: %zu", bullets.size());
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Stats")) {
			ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();
}