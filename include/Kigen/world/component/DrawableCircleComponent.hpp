//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_DRAWABLECIRCLECOMPONENT_HPP
#define YOSAI_DRAWABLECIRCLECOMPONENT_HPP

#include "Component.hpp"
#include <SFML/Graphics/CircleShape.hpp>


namespace kigen {
    class DrawableCircleComponent : public Component, public sf::Drawable {
    public:
        using Ptr = std::unique_ptr<DrawableCircleComponent>;
        explicit DrawableCircleComponent(float radius);

        Type type() const override;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void debug_draw(sf::RenderTarget &target, sf::RenderStates states) const;

        void set_radius(float radius);
        void set_texture(const sf::Texture& texture);
    private:
        sf::CircleShape m_circle;
    };
}

#endif //YOSAI_DRAWABLECIRCLECOMPONENT_HPP
