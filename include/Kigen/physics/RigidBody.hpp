//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.06.2020.
//

#ifndef YOSAI_RIGIDBODY_HPP
#define YOSAI_RIGIDBODY_HPP

#include "Shape.hpp"

namespace kigen {
    class RigidBody {
        friend  class PhysicsScene;
        friend  class Manifold;
    public:
        RigidBody(Shape::Ptr shape, Material material, sf::Vector2f position);
        bool isPendingDestruction() const { return m_is_pending_destruction;}
        void destroy() { m_is_pending_destruction = true; }
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
    private:
        bool m_is_pending_destruction {false};
    };
}


#endif //YOSAI_RIGIDBODY_HPP
