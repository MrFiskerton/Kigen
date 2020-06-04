//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.06.2020.
//

#include <cassert>
#include <Kigen/world/physics/RigidBody.hpp>

namespace kigen {
    RigidBody::RigidBody(const Shape::Ptr& shape, sf::Vector2f position, const Material::Ptr& material)
    : m_shape(shape), m_material(material) {
        assert(shape.get());
        m_lin.position = position;
        shape->compute_mass(material->density, m_mass);
    }

    void RigidBody::apply_force(const sf::Vector2f &force) { m_force += force; }

    void RigidBody::apply_impulse(const sf::Vector2f &impulse, const sf::Vector2f &contact_vector) {
        m_lin.velocity += m_mass.inverse_mass * impulse;
        m_ang.velocity += m_mass.inverse_inertia * cross(contact_vector, impulse);
    }
}

