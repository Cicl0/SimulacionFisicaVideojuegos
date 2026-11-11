#include "ForceRegistry.h"

// La fuerza fg actuará sobre todas las partículas (presentes y futuras) de ps
void 
ForceRegistry::bind(ForceGenerator* fg, ParticleSystem* ps) {
    if (!fg || !ps) return;

    // Añadir el generador de fuerzas a forceGens si no estaba ya
    auto it = std::find_if(forceGens.begin(), forceGens.end(),
        [fg](const std::unique_ptr<ForceGenerator>& p) { return p.get() == fg; });
    if (it == forceGens.end())
        forceGens.emplace_back(fg);   // el registro pasa a ser su dueño

    for (const auto& b : bindings)
        if (b.fg == fg && b.ps == ps) return;        // evitar duplicados
    bindings.push_back({ fg, ps });
}

// Enlaza TODOS los generadores de fuerzas existentes con ps
void 
ForceRegistry::bindAll(ParticleSystem* ps) {
    for (auto& g : forceGens) bind(g.get(), ps);
}

// Llamar si un ParticleSystem va a destruirse, para no dejar punteros colgantes
void 
ForceRegistry::removeParticleSystem(ParticleSystem* ps) {
    bindings.erase(std::remove_if(bindings.begin(), bindings.end(),
        [&](const Binding& b) { return b.ps == ps; }), bindings.end());
}

// Una vez por frame, ANTES de gen.integrate(dt)
// Cada generador de fuerzas recibe de golpe las partículas de todos los
// ParticleSystem a los que está enlazado, así que updateForce se llama una sola vez por cada generador de fuerzas
void 
ForceRegistry::updateForce(double dt) {
    for (auto& g : forceGens) {
        particles.clear();
        for (const auto& b : bindings) {
            if (b.fg != g.get()) continue;
            const auto& ps = b.ps->getAllParticles();     // lista viva
            particles.insert(particles.end(), ps.begin(), ps.end());
        }
        g->updateForce(particles, dt);
    }
}