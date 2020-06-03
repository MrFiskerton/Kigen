//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.06.2020.
//

#ifndef YOSAI_RIGIDBODY_HPP
#define YOSAI_RIGIDBODY_HPP

#include <Kigen/utils/Destructible.hpp>
#include "Shape.hpp"

namespace kigen {
    class RigidBody: public Destructible {
        friend class PhysicsScene;
        friend class Manifold;
        friend class PhysicsComponent;
    public:
        using Ptr = std::shared_ptr<RigidBody>;
        RigidBody(Shape::Ptr shape, sf::Vector2f position, Material material); //TODO material sharing
        const sf::Vector2f& get_position() { return m_lin.position; }
    protected:
        void apply_force(const sf::Vector2f& force);
        void apply_impulse(const sf::Vector2f& impulse, const sf::Vector2f& contact_vector);
    protected:
        Shape::Ptr m_shape;

        sf::Vector2f m_force;
        sf::Vector2f m_impulse;

        MassDependedComponent m_mass;
        LinearComponent m_lin;
        AngularComponent m_ang;
        Material m_material;
    };
}


#endif //YOSAI_RIGIDBODY_HPP
