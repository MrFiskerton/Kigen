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
    : m_body(body), m_lines(sf::Lines, 2) {
        m_lines[0].color = sf::Color::Magenta;
        m_lines[1].color = sf::Color::Magenta;
    }

    void DrawableDebugBody::entity_update(Entity &entity, float dt) {
        //m_lines[0]
        //m_orientation.setRotation(to_degrees(m_body->m_ang.orientation));
    }

    void DrawableDebugBody::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        //target.draw(m_velocity, states);
        m_body->m_shape->draw(target, states);
        target.draw(m_lines, states);
    }

    Component::Type DrawableDebugBody::type() const { return Component::Type::Drawable; }
}