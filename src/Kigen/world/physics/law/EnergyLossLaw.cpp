//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 09.06.2020.
//

#include "Kigen/world/physics/PhysicsLaw.hpp"

namespace kigen {
    using namespace physics;

    PhysicsLaw energy_loss("Energy loss", [](PhysicsScene &scene) {
        scene.for_body([](PhysicsBody &A) {
            A.lin().velocity *= ENERGY_LOSS_FACTOR;
            A.ang().velocity *= ENERGY_LOSS_FACTOR;
        });
    });
}

