//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_WORLD_HPP
#define YOSAI_WORLD_HPP

#include <Kigen/physics/PhysicsScene.hpp>
#include "Kigen/world/component/PhysicsComponent.hpp"
#include "Entity.hpp"

namespace kigen {
    class World {
    public:
        enum Layer : unsigned {
            L1 = 0, L2, SIZE
        };
    public:
        World();
        void add_entity(Entity::Ptr &entity, Layer layer = L1);

        void update(float dt);

        PhysicsScene& physics();
        Entity& get_layer(Layer layer);
    private:
        std::vector<Entity::Ptr> m_layers;
        PhysicsScene m_physics;
    };
}

#endif //YOSAI_WORLD_HPP
