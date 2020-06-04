//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#include "Kigen/world/component/DrawableCircleComponent.hpp"

namespace kigen {
    DrawableCircleComponent::DrawableCircleComponent(float radius) {
        set_radius(radius);
    }

    Component::Type kigen::DrawableCircleComponent::type() const {
        return Type::Drawable;
    }

    void DrawableCircleComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= m_circle.getTransform();
        states.blendMode = sf::BlendAdd;

        debug_draw(target, states);
        target.draw(m_circle, states);
    }

    void DrawableCircleComponent::set_radius(float radius) {
        m_circle.setRadius(radius);
        m_circle.setOrigin(radius * 0.5f, radius * 0.5f);
    }

    void DrawableCircleComponent::set_texture(const sf::Texture &texture) {
        m_circle.setTexture(&texture, true);
    }

    void DrawableCircleComponent::debug_draw(sf::RenderTarget &target, sf::RenderStates states) const {
        sf::CircleShape circle;
        circle.setFillColor(sf::Color::Magenta);
        circle.setPosition(m_circle.getPosition());
        circle.setOrigin(m_circle.getOrigin());
        //circle.setRadius(m_circle.getRadius());//10.f);
        circle.setRadius(10.f);

        target.draw(circle, states);
    }

}
