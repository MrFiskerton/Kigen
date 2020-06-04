//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#ifndef YOSAI_SHAPE_HPP
#define YOSAI_SHAPE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include "Kigen/world/physics/Models.hpp"
#include "Kigen/world/physics/Math.hpp"

namespace kigen {

    class Shape : public sf::Drawable {
    public:
        using Ptr = std::shared_ptr<Shape>;
        enum Type {
            Circle, SIZE
        };
    public:
        virtual void compute_mass(float density, MassDependedComponent &result) const = 0;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
        virtual Type type() const = 0;
    };

}

#endif //YOSAI_SHAPE_HPP
