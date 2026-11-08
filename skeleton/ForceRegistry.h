#pragma once

#include <vector>
#include <algorithm>
#include <memory>

#include "ForceGenerator.h"

class ForceRegistry
{
public:

    template <class T, class... Args>
    T* create(Args&&... args) {
        auto g = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = g.get();
        generators.push_back(std::move(g));
        return raw;
    }

    // Hace que el generador g afecte a la partícula p.
    void bind(ForceGenerator* g, Particle* p) { g->addParticle(p); }

    // Hace que todos los generadores afecten a p.
    void bindAll(Particle* p) { for (auto& g : generators) g->addParticle(p); }

    // Quita p de todos los generadores (llamar cuando la partícula muere).
    void unbindParticle(Particle* p) { for (auto& g : generators) g->removeParticle(p); }

    // Un único update por frame, antes de integrar las partículas.
    void update(double dt) { for (auto& g : generators) g->updateForce(dt); }

    void clear() { generators.clear(); }

private:
    std::vector<std::unique_ptr<ForceGenerator>> generators;
};

