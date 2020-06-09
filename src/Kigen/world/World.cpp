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
        for (auto& layer : m_layers) layer->update(dt); // Must be the first !!! Here apply players input as a force
        message_delivery();
        energy_loss();
        law_of_gravitation();
        m_physics.update(dt); // After update clear state ( applied forces and torque )
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

    PhysicsScene &World::physics() { return m_physics; }

    Entity &World::get_layer(World::Layer layer) { return *m_layers[layer]; }

    void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        for (const auto& layer : m_layers) target.draw(*layer, states);
    }

    void World::law_of_gravitation() {
        m_physics.for_body_pairs([&](RigidBody &A, RigidBody &B) {
            if (A.m_mass.is_infinite() && B.m_mass.is_infinite()) return;

            sf::Vector2f direction = B.m_lin.position - A.m_lin.position;
            float distance = length(direction);
            if (distance > GRAVITY_MIN_DISTANCE) return; // isn't close enough
            if (is_almost_zero(distance)) return;

            float F_scalar = G * A.m_mass.mass * B.m_mass.mass / sqr(distance);
            if(is_almost_zero(F_scalar)) return;

            sf::Vector2f force = (direction / distance) * F_scalar;

            A.apply_force(force);
            B.apply_force(-force);
        });
    }

    void World::energy_loss() {
        m_physics.for_body([](RigidBody& A) {
            A.m_lin.velocity *= ENERGY_LOSS_FACTOR;
            A.m_ang.velocity *= ENERGY_LOSS_FACTOR;
        });
    }

    Entity::Ptr World::create_entity() {
        return std::make_unique<Entity>(m_message_bus);
    }
}
