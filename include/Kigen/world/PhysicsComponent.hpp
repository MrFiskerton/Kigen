//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_PHYSICSCOMPONENT_HPP
#define YOSAI_PHYSICSCOMPONENT_HPP

#include <Kigen/physics/RigidBody.hpp>
#include "Component.hpp"

namespace kigen {
    class PhysicsComponent: public Component, public RigidBody {
    public:
        using Ptr = std::unique_ptr<PhysicsComponent>;

        Type type() const override { return Component::Type::Physics; }

        void entity_update(Entity &entity, float dt) override {

        }

        void on_start(Entity &entity) override {
            //Component::on_start(entity);
        }

    public:

    private:
    };
}

#endif //YOSAI_PHYSICSCOMPONENT_HPP
