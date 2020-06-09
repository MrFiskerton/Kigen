//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.05.2020.
//

#include "Yosai/states/GameState.hpp"

using namespace kigen;

GameState::GameState(StateControl &stack) : State(stack) {
    init_world_laws();

    for (int i = 0; i < 50; ++i) {
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

    m_world.get_layer(World::L1).setPosition(500, 500);

    //

    //
    sf::VertexArray array;
    int n = random(3, 7);
    float s = random(20.f, 60.f);
    for (int i = 0; i < n; i++){
        array.append( sf::Vector2f{random(-s, s)+ 65, random(-s, s)+65});
    }
//    array.append(sf::Vector2f{50, 50});
//    array.append(sf::Vector2f{200, 50});
//    array.append(sf::Vector2f{100, 150});

    auto polygon = std::make_shared<Polygon>(array);
    static PhysicsBody::Ptr physics_c = std::make_unique<PhysicsBody>(polygon, sf::Vector2f{500, 500}, Data::steel);
    auto poly_c = std::make_unique<DrawableDebugBody>(physics_c.get());
    m_world.get_layer(World::L1).add_component(poly_c);
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
    Entity::Ptr entity = m_world.create_entity();

    switch (t) {
        case 1: {
            auto circle = std::make_shared<Circle>(random(5.f, 15.f));
            PhysicsBody::Ptr physics_c = std::make_unique<PhysicsBody>(circle, position, Data::steel);
            m_world.physics().add_body(physics_c);
            entity->add_component<PhysicsBody>(physics_c);

//            auto circle_c = std::make_unique<DrawableCircle>(50.f);
//            circle_c->set_texture(Locator::locate<ResourceControl>().texture()[Textures::blue_star]);
//            entity->add_component(circle_c);
        }
            break;
        case 2: {
            auto circle = std::make_shared<Circle>(80.f);
            PhysicsBody::Ptr physics_c = std::make_unique<PhysicsBody>(circle, sf::Vector2f{500.f, 300.f},
                                                                       Data::super_solid);
            m_world.physics().add_body(physics_c);
            entity->add_component<PhysicsBody>(physics_c);

//            auto circle_c = std::make_unique<DrawableCircle>(50.f);
//            circle_c->set_texture(Locator::locate<ResourceControl>().texture()[Textures::circle_earth]);
//            entity->add_component(circle_c);
        }
    }
    return entity;
}

void GameState::init_world_laws() {
    m_world.add_physics_law(Law::energy_loss);
    m_world.add_physics_law(Law::gravitation);
}
