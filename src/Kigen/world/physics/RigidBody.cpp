//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.06.2020.
//

#include <Kigen/world/physics/RigidBody.hpp>

namespace kigen {
    RigidBody::RigidBody(const Shape::Ptr& shape, sf::Vector2f position, const Material::Ptr& material)
    : m_shape(shape), m_material(material), m_mass(shape, material) {
        assert(shape.get());
        m_lin.position = position;
    }

    void RigidBody::apply_force(const sf::Vector2f &force) { m_lin.force += force; }

    void RigidBody::apply_impulse(const sf::Vector2f &impulse, const sf::Vector2f &contact_vector) {
        m_lin.velocity += m_mass.inverse_mass * impulse;
        m_ang.velocity += m_mass.inverse_inertia * cross(contact_vector, impulse);
    }

    void RigidBody::stop() {
        m_lin.velocity = {0.f, 0.f};
        m_ang.velocity = 0.f;
    }

    sf::Vector2f RigidBody::to_model_space(const sf::Vector2f &p) {
        if(is_need_update_transform) update_transform();
        return m_inverse_transform * p;
    }

    sf::Vector2f RigidBody::to_world_space(const sf::Vector2f &p) {
        if(is_need_update_transform) update_transform();
        return m_transform * p;
    }

    void RigidBody::clean_applied_force() {
        m_lin.force = {0.f, 0.f};
        m_ang.torque = 0.f;
        is_need_update_transform = true; //TODO
    }

    void RigidBody::update_transform() {
        m_transform = sf::Transform::Identity;
        m_transform.rotate(m_ang.orientation);
        m_transform.translate(m_lin.position);
        //TODO scale
        m_inverse_transform = m_transform.getInverse();
        is_need_update_transform = false;
    }
}

