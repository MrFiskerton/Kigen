//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#ifndef YOSAI_VECTOR_HPP
#define YOSAI_VECTOR_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <Kigen/utils/Palette.hpp>
#include <Kigen/world/physics/Math.hpp>
#include <Kigen/utils/Logger.hpp>

namespace kigen {
    class Vector : public sf::Drawable, sf::Transformable {
    public:
        Vector();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void from(const sf::Vector2f& from);
        void to(const sf::Vector2f& from);
    private:
        sf::VertexArray line;
        sf::CircleShape arrow;
    };
}

#endif //YOSAI_VECTOR_HPP
