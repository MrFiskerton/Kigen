//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#include <Kigen/world/message/Message.hpp>
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
        m_physics_scene.clear_state(); //  Clear applied forces, torque, collisions
        for (auto& layer : m_layers) layer->update(dt);  
        for (auto& law : m_physics_laws) law(m_physics_scene); // Apply the laws of physics

        m_physics_scene.update(dt); // Apply forces and integrate; Sends collision messages;
        message_delivery();
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
        for (const auto& collison : m_physics_scene.get_collisions()) target.draw(collison, states);
    }

    Entity::Ptr World::create_entity() {
        return std::make_unique<Entity>(m_message_bus);
    }
}
