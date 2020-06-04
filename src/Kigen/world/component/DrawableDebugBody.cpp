//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#include "Kigen/world/component/DrawableDebugBody.hpp"

namespace kigen {
//    void DrawableDebugBody::on_start(Entity &entity) {
//        m_body = entity.get_component<PhysicsBody>("physics");
//        assert(m_body);
//    }

    DrawableDebugBody::DrawableDebugBody(PhysicsBody *body)
    : m_body(body) {
        m_origin.setRadius(2.f);
        m_origin.setFillColor(sf::Color::Red);
        m_origin.setOrigin(m_origin.getRadius() * 0.5f, m_origin.getRadius() * 0.5f);
    }

    void DrawableDebugBody::entity_update(Entity &entity, float dt) {
        m_velocity.to(m_body->m_lin.velocity);
//        if (m_body->get_parent_UID() == 2)
//        Logger::info() << "[" << m_body->get_parent_UID() << "] " << to_degrees(m_body->m_ang.velocity) << "\n";
    }

    void DrawableDebugBody::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        m_body->m_shape->draw(target, states);
        target.draw(m_velocity, states);

        states.transform *= m_origin.getTransform();
        target.draw(m_origin, states );
    }

    Component::Type DrawableDebugBody::type() const { return Component::Type::Drawable; }
}