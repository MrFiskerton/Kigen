//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.05.2020.
//

#include "Yosai/states/GameState.hpp"

using namespace kigen;

GameState::GameState(StateControl &stack) : State(stack) {
    for (int i = 0; i < 15; ++i) {
        auto entity = create_entity();
        m_world.add_entity(entity, World::L1);
    }
}

GameState::~GameState() {}

void GameState::draw(sf::RenderTarget &target) {
    static sf::CircleShape shape(100.f);

    shape.setTexture(&Locator::locate<ResourceControl>().texture()[Textures::blue_star]);
    //shape.setFillColor(sf::Color::Green);

    target.draw(shape);
}

bool GameState::update(const sf::Time &delta) {
    return false;
}

bool GameState::handleEvent(const sf::Event &event) {
    return false;
}

Entity::Ptr GameState::create_entity() {
    Entity::Ptr entity = std::make_unique<Entity>();

    auto circle = std::make_shared<Circle>(30.f);
    auto body = std::make_shared<RigidBody>(circle, sf::Vector2f{50.f, 50.f}, Data::iron);
    m_world.physics().add_body(body);
    PhysicsComponent::Ptr physics_c= std::make_unique<PhysicsComponent>(body);
    physics_c->set_name("physics");
    entity->add_component<PhysicsComponent>(physics_c);
    return entity;
}