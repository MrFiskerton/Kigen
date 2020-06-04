//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_WORLD_HPP
#define YOSAI_WORLD_HPP

#include <Kigen/physics/PhysicsScene.hpp>
#include <Kigen/world/component/PhysicsComponent.hpp>
#include <Kigen/world/component/DrawableCircleComponent.hpp>
#include "Entity.hpp"

namespace kigen {
    class World : public sf::Drawable {
    public:
        enum Layer : unsigned {
            L1 = 0, SIZE
        };
    public:
        World();
        void add_entity(Entity::Ptr &entity, Layer layer = L1);
        void update(float dt);
        PhysicsScene &physics();
        Entity &get_layer(Layer layer);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        std::vector<Entity::Ptr> m_layers;
        PhysicsScene m_physics;
    };
}

#endif //YOSAI_WORLD_HPP
