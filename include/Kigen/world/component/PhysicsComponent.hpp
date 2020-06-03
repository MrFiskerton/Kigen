//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_PHYSICSCOMPONENT_HPP
#define YOSAI_PHYSICSCOMPONENT_HPP

#include <utility>
#include <Kigen/physics/RigidBody.hpp>
#include "Kigen/world/component/Component.hpp"
#include "Kigen/world/Entity.hpp"

namespace kigen {
    class PhysicsComponent: public Component {
    public:
        using Ptr = std::unique_ptr<PhysicsComponent>;

        explicit PhysicsComponent(RigidBody::Ptr body) : body(std::move(body)){}

        Type type() const override { return Component::Type::Physics; }

        void entity_update(Entity &entity, float dt) override {
            entity.set_world_position(body->m_lin.position);
        }

        void on_start(Entity &entity) override {
            //Component::on_start(entity);
        }

    public:
        RigidBody::Ptr body;
    };
}

#endif //YOSAI_PHYSICSCOMPONENT_HPP
