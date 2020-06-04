//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#ifndef YOSAI_CIRCLE_HPP
#define YOSAI_CIRCLE_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Kigen/world/physics/shape/Shape.hpp"

namespace kigen{
    class Circle : public Shape {
    public:
        using Ptr = std::shared_ptr<Circle>;

        explicit Circle(float radius) : radius(radius),  circle(radius) {
            circle.setFillColor(sf::Color::Transparent);
            circle.setOrigin(radius * 0.5f, radius * 0.5f);
            circle.setOutlineThickness(1.f);
            circle.setOutlineColor(sf::Color::Red);
        };

        void compute_mass(float density, MassDependedComponent &result) const override {
            result.mass = PI * radius * radius * density;
            result.inverse_mass = ((result.mass != 0.f) ? 1.0f / result.mass : 0.0f);
            result.inertia = result.mass * radius * radius * 0.5f;
            result.inverse_inertia = ((result.inertia != 0.f) ? 1.0f / result.inertia : 0.0f);
        }

        //TODO
        Type type() const override { return Shape::Type::Circle; }

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            states.transform *= circle.getTransform();
            target.draw(circle, states);
        }

    public:
        float radius;

    private:
        sf::CircleShape circle;
    };
}

#endif //YOSAI_CIRCLE_HPP
