//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.05.2020.
//

#include "Yosai/states/GameState.hpp"

using namespace kigen;

GameState::GameState(StateControl &stack) : State(stack) {
    for (int i = 0; i < 20; ++i) {
        auto entity = create_entity({400, 400}, 1);
        m_world.add_entity(entity, World::L1);
    }

    for (int i = 0; i < 20; ++i) {
        auto entity = create_entity({800, 400}, 1);
        m_world.add_entity(entity, World::L1);
    }

    auto A = create_entity({100.f, 300.f}, 2);
    m_world.add_entity(A);

    auto B = create_entity({900.f, 300.f}, 2);
    m_world.add_entity(B);

//    auto C = create_entity({800.f, 270.f});
//    m_world.add_entity(C);

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


Entity::Ptr GameState::create_entity(sf::Vector2f position, int t) {
    Entity::Ptr entity = std::make_unique<Entity>();

    switch (t) {
        case 1: {
            auto circle = std::make_shared<Circle>(random(10.f, 30.f));
            PhysicsBody::Ptr physics_c = std::make_unique<PhysicsBody>(circle, position, Data::steel);
            m_world.physics().add_body(physics_c);
            entity->add_component<PhysicsBody>(physics_c);

            auto circle_c = std::make_unique<DrawableCircle>(50.f);
            circle_c->set_texture(Locator::locate<ResourceControl>().texture()[Textures::blue_star]);
            entity->add_component(circle_c);
        }
            break;
        case 2: {
            auto circle = std::make_shared<Circle>(80.f);
            PhysicsBody::Ptr physics_c = std::make_unique<PhysicsBody>(circle, sf::Vector2f{500.f, 300.f},
                                                                       Data::super_solid);
            m_world.physics().add_body(physics_c);
            entity->add_component<PhysicsBody>(physics_c);

            auto circle_c = std::make_unique<DrawableCircle>(50.f);
            circle_c->set_texture(Locator::locate<ResourceControl>().texture()[Textures::circle_earth]);
            entity->add_component(circle_c);
        }
    }
    return entity;
}