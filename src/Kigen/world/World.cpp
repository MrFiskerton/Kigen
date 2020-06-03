//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#include "Kigen/world/World.hpp"

namespace kigen {
    World::World() {
        for (std::size_t i = 0; i < Layer::SIZE; ++i) {
            m_layers.emplace_back(std::make_unique<Entity>());
            m_layers.back()->set_world(this);
        }
    }

    void World::create_entity() {
        Entity::Ptr entity = std::make_unique<Entity>();

        PhysicsComponent::Ptr physic_c = m_physics.add_body(std::make_unique<RigidBody>());
        physic_c->set_name("physic");
        entity->add_component(physic_c);

        return std::move(e);
    }
}
