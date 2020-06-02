//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#ifndef YOSAI_SHAPE_HPP
#define YOSAI_SHAPE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include "Models.hpp"
#include "Math.hpp"
#include <Kigen/utils/Type.hpp>

namespace kigen {

    class Shape : public sf::Drawable {
    public:
        typedef std::shared_ptr<Shape> Ptr;
    public:
        virtual MassDependedComponent compute_mass(float density) const = 0;
        virtual Type<Shape> type() const = 0;
    };


    class Circle : public Shape {
    public:
        explicit Circle(float radius) : radius(radius) {};

        MassDependedComponent compute_mass(float density) const override {
            MassDependedComponent result{};
            result.mass = PI * radius * radius * density;
            result.inverse_mass = ((result.mass == 0.f) ? 1.0f / result.mass : 0.0f);
            result.inertia = result.mass * radius * radius;
            result.inverse_inertia = ((result.inertia == 0.f) ? 1.0f / result.inertia : 0.0f);
            return result;
        }

        //TODO
        Type<Shape> type() const override { return {}; }

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

        }

    public:
        float radius;
    };
}

#endif //YOSAI_SHAPE_HPP
