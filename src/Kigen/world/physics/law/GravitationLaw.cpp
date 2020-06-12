//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 09.06.2020.
//

#include "Kigen/world/physics/PhysicsLaw.hpp"

namespace kigen {
    using namespace physics;

    PhysicsLaw gravitation("Gravitation", [](PhysicsScene &scene) {
        scene.for_body_pairs([&](PhysicsBody &A, PhysicsBody &B) {
            if (A.is_static() && B.is_static()) return;

            sf::Vector2f direction = B.lin().position - A.lin().position;
            float distance = length(direction);
            if (distance > GRAVITY_MIN_DISTANCE) return; // isn't close enough
            if (is_almost_zero(distance)) return;

            float F_scalar = G * A.m().mass * B.m().mass / sqr(distance);
            if (is_almost_zero(F_scalar)) return;

            sf::Vector2f force = (direction / distance) * F_scalar;

            A.apply_force(force);
            B.apply_force(-force);
        });
    });
}

