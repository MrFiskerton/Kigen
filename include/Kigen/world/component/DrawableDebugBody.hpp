//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#ifndef YOSAI_DRAWABLEDEBUGBODY_HPP
#define YOSAI_DRAWABLEDEBUGBODY_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "DrawableComponent.hpp"
#include "PhysicsBody.hpp"

namespace kigen {
    class DrawableDebugBody : public DrawableComponent {
    public:
        using Ptr = std::unique_ptr<DrawableDebugBody>;

        explicit DrawableDebugBody(PhysicsBody *body);
        void entity_update(Entity &entity, float dt) override;
        Type type() const override;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        PhysicsBody *m_body;
        sf::CircleShape m_origin;
        sf::VertexArray m_lines;
    };
}

#endif //YOSAI_DRAWABLEDEBUGBODY_HPP
