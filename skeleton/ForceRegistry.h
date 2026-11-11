#pragma once

#include <vector>
#include <algorithm>
#include <memory>

#include "ForceGenerator.h"
#include "ParticleSystem.h"

class ParticleSystem;

class ForceRegistry
{
public:
    // Crea un generador de fuerzas de tipo T, lo guarda y devuelve un puntero
    template <class T, class... Args>
    T* create(Args&&... args) {
        auto g = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = g.get();
        forceGens.push_back(std::move(g));
        return raw;
    }

    // La fuerza fg actuará sobre todas las partículas (presentes y futuras) de ps
    void bind(ForceGenerator* fg, ParticleSystem* ps);

    // Enlaza TODOS los generadores de fuerzas existentes con ps
    void bindAll(ParticleSystem* ps);

    // Llamar si un Generator va a destruirse, para no dejar punteros colgantes
    void removeParticleSystem(ParticleSystem* ps);

    // Una vez por frame, ANTES de gen.integrate(dt)
    // Cada generador de fuerzas recibe de golpe las partículas de todos los
    // Generator a los que está enlazado, así que updateForce se llama una sola vez
    void updateForce(double dt);

    void clear() { bindings.clear(); forceGens.clear(); }

private:
    struct Binding { ForceGenerator* fg; ParticleSystem* ps; };

    std::vector<std::unique_ptr<ForceGenerator>> forceGens;
    std::vector<Binding> bindings;
    std::vector<Particle*> particles;
};

