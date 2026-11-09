#pragma once

#include <vector>
#include <algorithm>
#include <memory>

#include "ForceGenerator.h"
#include "Generator.h"

class Generator;

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

    // La fuerza fg actuará sobre todas las partículas (presentes y futuras) de gen
    void bind(ForceGenerator* fg, Generator* gen);

    // Enlaza TODOS los generadores de fuerzas existentes con gen
    void bindAll(Generator* gen);

    // Llamar si un Generator va a destruirse, para no dejar punteros colgantes
    void removeGenerator(Generator* gen);

    // Una vez por frame, ANTES de gen.integrate(dt)
    // Cada generador de fuerzas recibe de golpe las partículas de todos los
    // Generator a los que está enlazado, así que updateForce se llama una sola vez
    void updateForce(double dt);

    void clear() { bindings.clear(); forceGens.clear(); }

private:
    struct Binding { ForceGenerator* fg; Generator* gen; };

    std::vector<std::unique_ptr<ForceGenerator>> forceGens;
    std::vector<Binding> bindings;
    std::vector<Particle*> particles;
};

