//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 09.06.2020.
//

#include "Kigen/world/physics/PhysicsLaw.hpp"

namespace kigen {
    namespace Law {
        using namespace physics;

        PhysicsLaw energy_loss("Energy loss", [](PhysicsScene &scene) {
            scene.for_body([](RigidBody &A) {
                A.m_lin.velocity *= ENERGY_LOSS_FACTOR;
                A.m_ang.velocity *= ENERGY_LOSS_FACTOR;
            });
        });
    }
}

