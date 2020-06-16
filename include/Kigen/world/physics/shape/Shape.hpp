//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#ifndef YOSAI_SHAPE_HPP
#define YOSAI_SHAPE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include "Kigen/world/physics/Math.hpp"
#include <Kigen/utils/Palette.hpp>
#include <Kigen/utils/Logger.hpp>

namespace kigen {

    class Shape : public sf::Drawable {
    public:
        using Ptr = std::shared_ptr<Shape>;
        enum Type {
            Circle, Polygon, SIZE
        };
    public:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
        virtual Type type() const = 0;

        float get_area() const { return m_area; }
        float get_inertia() const { return m_inertia; }
    protected:
        float m_area, m_inertia;
    };

}

#endif //YOSAI_SHAPE_HPP
