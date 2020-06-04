//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#include <Kigen/world/component/PhysicsBody.hpp>
#include <Kigen/world/component/DrawableDebugBody.hpp>

namespace  kigen {
    PhysicsBody::PhysicsBody(const Shape::Ptr& shape, sf::Vector2f position, const Material::Ptr& material)
    : RigidBody(shape, position, material){
        Component::set_name("physics");
    }

    Component::Type PhysicsBody::type() const { return Component::Type::Physics; }

    void PhysicsBody::entity_update(Entity &entity, float dt) {
        entity.set_world_position(m_lin.position);
//            Logger::notify() << "[" << get_parent_UID() << "] "
//            << body->m_lin.position.x << " " << body->m_lin.position.y << Logger::endlf();
    }

    void PhysicsBody::on_start(Entity &entity) {
        auto debug_c = std::make_unique<DrawableDebugBody>(this);
        entity.add_component(debug_c);
    }
}
