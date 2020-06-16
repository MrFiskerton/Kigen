//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_DRAWABLECIRCLE_HPP
#define YOSAI_DRAWABLECIRCLE_HPP

#include "DrawableComponent.hpp"
#include <SFML/Graphics/CircleShape.hpp>


namespace kigen {
    class DrawableCircle : public DrawableComponent {
    public:
        using Ptr = std::unique_ptr<DrawableCircle>;
        explicit DrawableCircle(float radius);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        void set_radius(float radius);
        void set_texture(const sf::Texture& texture);
    private:
        sf::CircleShape m_circle;
    };
}

#endif //YOSAI_DRAWABLECIRCLE_HPP
