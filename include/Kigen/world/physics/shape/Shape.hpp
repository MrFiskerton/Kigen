//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#ifndef YOSAI_SHAPE_HPP
#define YOSAI_SHAPE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include "Kigen/world/physics/Models.hpp"
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
        void compute_mass(float density, MassDependedComponent &result) {
            result.compute_mass(m_area, density);
            result.compute_inertia(m_inertia);
        }

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
        virtual Type type() const = 0;

    protected:
        float m_area, m_inertia;
    };

}

#endif //YOSAI_SHAPE_HPP
