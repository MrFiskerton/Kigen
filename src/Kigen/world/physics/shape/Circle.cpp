//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 07.06.2020.
//

#include "Kigen/world/physics/shape/Circle.hpp"

namespace kigen {
    Circle::Circle(float radius) : radius(radius), circle(radius) {
        m_area = PI * radius * radius;
        // Thin, solid disk of radius r and mass m.
        // See https://en.wikipedia.org/wiki/List_of_moments_of_inertia
        m_inertia = radius * radius * 0.5f;  // Iz

        circle.setFillColor(sf::Color::Transparent);
        circle.setOrigin(radius * 0.5f, radius * 0.5f);
        circle.setOutlineThickness(1.f);
        circle.setOutlineColor(Palette::Lavender);
    }

    Shape::Type Circle::type() const { return Shape::Type::Circle; }

    void Circle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= circle.getTransform();
        target.draw(circle, states);
    }
}

