//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#ifndef YOSAI_SHAPE_HPP
#define YOSAI_SHAPE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include "Models.hpp"
#include "Math.hpp"

namespace kigen {

    class Shape : public sf::Drawable {
    public:
        typedef std::shared_ptr<Shape> Ptr;
        enum Type { Circle = 0 };
    public:
        virtual MassDependedComponent compute_mass(float density) const = 0;
        virtual Type type() const = 0;
    };


    class Circle : public Shape {
    public:
        explicit Circle(float radius) : m_radius(radius) {};

        MassDependedComponent compute_mass(float density) const override {
            MassDependedComponent result{};
            result.mass = PI * m_radius * m_radius * density;
            result.inverse_mass = ((result.mass == 0.f) ? 1.0f / result.mass : 0.0f);
            result.inertia = result.mass * m_radius * m_radius;
            result.inverse_inertia = ((result.inertia == 0.f) ? 1.0f / result.inertia : 0.0f);
            return result;
        }

        Type type() const override { return Type::Circle; }

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

        }

    private:
        float m_radius;
    };
}

#endif //YOSAI_SHAPE_HPP
