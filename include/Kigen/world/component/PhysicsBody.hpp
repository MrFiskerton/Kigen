//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_PHYSICSBODY_HPP
#define YOSAI_PHYSICSBODY_HPP

#include <utility>
#include <Kigen/world/physics/RigidBody.hpp>
#include "Kigen/world/component/Component.hpp"
#include "Kigen/world/Entity.hpp"

namespace kigen {
    class PhysicsBody: public Component, public RigidBody {
    public:
        using Ptr = std::unique_ptr<PhysicsBody>;

        void on_start(Entity &entity) override;

        explicit PhysicsBody(const Shape::Ptr& shape, sf::Vector2f position, const Material::Ptr& material);
        Type type() const override;
        void entity_update(Entity &entity, float dt) override;
    };
}

#endif //YOSAI_PHYSICSBODY_HPP
