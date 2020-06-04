//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_PHYSICSCOMPONENT_HPP
#define YOSAI_PHYSICSCOMPONENT_HPP

#include <utility>
#include <Kigen/world/physics/RigidBody.hpp>
#include "Kigen/world/component/Component.hpp"
#include "Kigen/world/Entity.hpp"

namespace kigen {
    class PhysicsComponent: public Component {
    public:
        using Ptr = std::unique_ptr<PhysicsComponent>;

        explicit PhysicsComponent(RigidBody::Ptr body);
        Type type() const override;
        void entity_update(Entity &entity, float dt) override;
    public:
        RigidBody::Ptr body;
    };
}

#endif //YOSAI_PHYSICSCOMPONENT_HPP
