//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#include "Kigen/world/component/DrawableCircle.hpp"

namespace kigen {
    DrawableCircle::DrawableCircle(float radius) {
        set_radius(radius);
    }

    Component::Type kigen::DrawableCircle::type() const {
        return Type::Drawable;
    }

    void DrawableCircle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= m_circle.getTransform();
        states.blendMode = sf::BlendAdd;

        target.draw(m_circle, states);
    }

    void DrawableCircle::set_radius(float radius) {
        m_circle.setRadius(radius);
        m_circle.setOrigin(radius * 0.5f, radius * 0.5f);
    }

    void DrawableCircle::set_texture(const sf::Texture &texture) {
        m_circle.setTexture(&texture, true);
    }
}
