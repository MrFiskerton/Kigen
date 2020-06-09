//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#include "Kigen/world/World.hpp"

namespace kigen {
    using namespace physics;

    World::World() {
        for (std::size_t i = 0; i < Layer::SIZE; ++i) {
            m_layers.emplace_back(std::make_unique<Entity>(m_message_bus));
            m_layers.back()->set_world(this);
        }
    }

    void World::update(float dt) {
        for (auto& layer : m_layers) layer->update(dt);  // Note: Must be before physics scene update !
        for (auto& law : m_physics_laws) law(m_physics_scene); // Apply the laws of physics
        message_delivery();
        m_physics_scene.update(dt); // After update clears state ( applied forces and torque )
    }

    void World::message_delivery() {
        Message message;
        while(m_message_bus.poll(message)) {
            for(auto& layer: m_layers) layer->receive_message(message);
        }
    }

    void World::add_entity(Entity::Ptr &entity, World::Layer layer) {
        m_layers[layer]->add_child(entity);
    }

    void World::add_physics_law(const PhysicsLaw &law) {
        m_physics_laws.push_back(law);
    }

    PhysicsScene &World::physics() { return m_physics_scene; }

    Entity &World::get_layer(World::Layer layer) { return *m_layers[layer]; }

    void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        for (const auto& layer : m_layers) target.draw(*layer, states);
    }

    Entity::Ptr World::create_entity() {
        return std::make_unique<Entity>(m_message_bus);
    }
}
