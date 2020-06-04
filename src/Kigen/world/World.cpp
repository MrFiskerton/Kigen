//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#include "Kigen/world/World.hpp"

namespace kigen {
    World::World() {
        for (std::size_t i = 0; i < Layer::SIZE; ++i) {
            m_layers.emplace_back(std::make_unique<Entity>());
            m_layers.back()->set_world(this);
        }
    }

    void World::update(float dt) {
        for (auto& layer : m_layers) layer->update(dt); // Must be the first !!! Here apply players input as a force
        m_physics.update(dt); // After update clear state ( applied forces and torque )
    }

    void World::add_entity(Entity::Ptr &entity, World::Layer layer) {
        m_layers[layer]->add_child(entity);
    }

    PhysicsScene &World::physics() { return m_physics; }

    Entity &World::get_layer(World::Layer layer) { return *m_layers[layer]; }

    void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        for (const auto& layer : m_layers) target.draw(*layer, states);
    }
}
