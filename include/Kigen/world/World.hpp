//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_WORLD_HPP
#define YOSAI_WORLD_HPP

#include <Kigen/physics/PhysicsScene.hpp>
#include "PhysicsComponent.hpp"
#include "Entity.hpp"

namespace kigen {
    class World {
    public:
        enum Layer : unsigned {
            L1 = 0, L2, SIZE
        };
    public:
        World();
        void create_entity();

    private:
        std::vector<Entity::Ptr> m_layers;
        PhysicsScene m_physics;
    };
}

#endif //YOSAI_WORLD_HPP
