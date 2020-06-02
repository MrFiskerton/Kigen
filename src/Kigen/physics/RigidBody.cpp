//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.06.2020.
//

#include <cassert>
#include "Kigen/physics/RigidBody.hpp"

namespace kigen {
    RigidBody::RigidBody(Shape::Ptr shape, Material material, sf::Vector2f position) {
        assert( shape );
        m_mass = shape->compute_mass(material.density);
    }

    void RigidBody::apply_force(const sf::Vector2f &force) { m_force += force; }

    void RigidBody::apply_impulse(const sf::Vector2f &impulse, const sf::Vector2f &contact_vector) {
        m_lin.velocity += m_mass.inverse_mass * impulse;
        m_ang.velocity += m_mass.inverse_inertia * cross(contact_vector, impulse);
    }
}

