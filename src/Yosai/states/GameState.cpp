//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.05.2020.
//

#include <Kigen/world/component/DrawableDebugBody.hpp>
#include "Yosai/states/GameState.hpp"

using namespace kigen;

GameState::GameState(StateControl &stack) : State(stack) {
    for (int i = 0; i < 10; ++i) {
        auto entity = create_entity({400, 400});
        m_world.add_entity(entity, World::L1);
    }
    auto A = create_entity({200.f, 300.f});
    m_world.add_entity(A);

    auto B = create_entity({200.f, 600.f});
    m_world.add_entity(B);

    auto C = create_entity({800.f, 270.f});
    m_world.add_entity(C);

    m_world.get_layer(World::L1).setPosition(0, 0);
}

GameState::~GameState() {}

void GameState::draw(sf::RenderTarget &target) {
    target.draw(m_world);
}

bool GameState::update(const sf::Time &delta) {
    m_world.update(delta.asSeconds());
    return false;
}

bool GameState::handleEvent(const sf::Event &event) {
    return false;
}

Entity::Ptr GameState::create_entity(sf::Vector2f position) {
    Entity::Ptr entity = std::make_unique<Entity>();

    auto circle = std::make_shared<Circle>(15.f);
    PhysicsBody::Ptr physics_c= std::make_unique<PhysicsBody>(circle, position, Data::iron);
    m_world.physics().add_body(physics_c);
    entity->add_component<PhysicsBody>(physics_c);

    auto circle_c = std::make_unique<DrawableCircle>(50.f);
    circle_c->set_texture(Locator::locate<ResourceControl>().texture()[Textures::blue_star]);
    entity->add_component(circle_c);

    return entity;
}