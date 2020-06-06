//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#ifndef YOSAI_CIRCLE_HPP
#define YOSAI_CIRCLE_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include "Kigen/world/physics/shape/Shape.hpp"

namespace kigen{
    class Circle : public Shape {
    public:
        using Ptr = std::shared_ptr<Circle>;

        explicit Circle(float radius) : radius(radius),  circle(radius) {
            circle.setFillColor(sf::Color::Transparent);
            circle.setOrigin(radius * 0.5f, radius * 0.5f);
            circle.setOutlineThickness(1.f);
            circle.setOutlineColor(Palette::Lavender);
        };

        void compute_mass(float density, MassDependedComponent &result) const override {
            result.compute_mass(PI * radius * radius, density);

            // Thin, solid disk of radius r and mass m.
            // See https://en.wikipedia.org/wiki/List_of_moments_of_inertia
            result.compute_inertia(radius * radius * 0.5f); // Iz
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
