#include "ForceRegistry.h"

// La fuerza fg actuará sobre todas las partículas (presentes y futuras) de gen
void 
ForceRegistry::bind(ForceGenerator* fg, Generator* gen) {
    for (const auto& b : bindings)
        if (b.fg == fg && b.gen == gen) return;        // evitar duplicados
    bindings.push_back({ fg, gen });
}

// Enlaza TODOS los generadores de fuerzas existentes con gen
void 
ForceRegistry::bindAll(Generator* gen) {
    for (auto& g : forceGens) bind(g.get(), gen);
}

// Llamar si un Generator va a destruirse, para no dejar punteros colgantes
void 
ForceRegistry::removeGenerator(Generator* gen) {
    bindings.erase(std::remove_if(bindings.begin(), bindings.end(),
        [&](const Binding& b) { return b.gen == gen; }), bindings.end());
}

// Una vez por frame, ANTES de gen.integrate(dt)
// Cada generador de fuerzas recibe de golpe las partículas de todos los
// Generator a los que está enlazado, así que updateForce se llama una sola vez
void 
ForceRegistry::updateForce(double dt) {
    for (auto& g : forceGens) {
        particles.clear();
        for (const auto& b : bindings) {
            if (b.fg != g.get()) continue;
            const auto& ps = b.gen->getParticles();     // lista viva
            particles.insert(particles.end(), ps.begin(), ps.end());
        }
        g->updateForce(particles, dt);
    }
}