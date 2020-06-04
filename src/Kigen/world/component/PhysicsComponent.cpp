//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#include <Kigen/world/component/PhysicsComponent.hpp>

namespace  kigen {
    PhysicsComponent::PhysicsComponent(kigen::RigidBody::Ptr body) : body(std::move(body)){}

    Component::Type PhysicsComponent::type() const { return Component::Type::Physics; }

    void PhysicsComponent::entity_update(Entity &entity, float dt) {
        entity.set_world_position(body->m_lin.position);
//            Logger::notify() << "[" << get_parent_UID() << "] "
//            << body->m_lin.position.x << " " << body->m_lin.position.y << Logger::endlf();
    }
}
