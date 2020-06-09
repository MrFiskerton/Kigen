//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_WORLD_HPP
#define YOSAI_WORLD_HPP

#include <Kigen/world/physics/PhysicsScene.hpp>
#include <Kigen/world/component/PhysicsBody.hpp>
#include <Kigen/world/component/DrawableCircle.hpp>
#include <Kigen/world/physics/PhysicsLaw.hpp>
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
        void add_physics_law(const PhysicsLaw& law);
        Entity::Ptr create_entity();
        void update(float dt);
        PhysicsScene &physics();
        Entity &get_layer(Layer layer);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        void message_delivery();
    public:
        MessageBus m_message_bus;
    private:
        std::vector<Entity::Ptr> m_layers;
        std::vector<PhysicsLaw> m_physics_laws;
        PhysicsScene m_physics_scene;
    };
}

#endif //YOSAI_WORLD_HPP
