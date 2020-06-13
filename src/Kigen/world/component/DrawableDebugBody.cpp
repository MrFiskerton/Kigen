//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#include <Yosai/id/ResourceIdentifiers.hpp>
#include "Kigen/world/component/DrawableDebugBody.hpp"
#include <Kigen/world/physics/Manifold.hpp>

namespace kigen {
//    void DrawableDebugBody::on_attach(Entity &entity) {
//        m_body = entity.get_component<PhysicsBody>("physics");
//        assert(m_body);
//    }

    DrawableDebugBody::DrawableDebugBody(PhysicsBody *body)
    : m_body(body) {
        m_origin.setRadius(2.f);
        m_origin.setFillColor(Palette::Lavender);
        m_origin.setOrigin(m_origin.getRadius() * 0.5f, m_origin.getRadius() * 0.5f);

        m_text_UID.setFont(Locator::locate<ResourceControl>().font()[Fonts::ID::DigitalDisplay]);
        m_text_UID.setFillColor(Palette::LemonChiffon);
        m_text_UID.setCharacterSize(12); // in pixels, not points!
        m_text_UID.setPosition(m_origin.getOrigin() + sf::Vector2f{-10.f, 20.f});
        m_text_UID.setString(std::to_string(body->get_owner_UID()));
    }

    void DrawableDebugBody::entity_update(Entity &entity, float dt) {
        m_velocity.to(m_body->lin().velocity);
    }

    void DrawableDebugBody::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        m_body->shape()->draw(target, states);

        target.draw(m_velocity, states);
        target.draw(m_text_UID, states);

        states.transform *= m_origin.getTransform();
        target.draw(m_origin, states );
    }
}