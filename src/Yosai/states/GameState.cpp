//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.05.2020.
//

#include "Yosai/states/GameState.hpp"

using namespace kigen;

GameState::GameState(StateControl &stack) : State(stack) {
    init_world_laws();
    init_factory();

    for (int i = 0; i < 100; ++i) {
        auto entity = m_factory.create("small_circle");
        m_world.add_entity(entity, World::L1);
    }
//    auto A = m_factory.create("huge_circle");
//    m_world.add_entity(A);

    auto B = m_factory.create("huge_circle");
    m_world.add_entity(B);

    //-------
    std::vector<sf::Vector2f> points ;
    int n = random(10, 70);
    float s = random(80.f, 150.f);
    for (int i = 0; i < n; i++) points.emplace_back(random(-s, s), random(-s, s));


    auto polygon = std::make_shared<Polygon>(points);
    static PhysicsBody::Ptr physics_c = std::make_unique<PhysicsBody>(polygon, sf::Vector2f{500, 500}, Data::steel);
    auto poly_c = std::make_unique<DrawableDebugBody>(physics_c.get());
    m_world.get_layer(World::L1).add_component(poly_c);
    m_world.get_layer(World::L1).add_component(physics_c);
    //----------
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

void GameState::init_world_laws() {
    m_world.add_physics_law(Law::energy_loss);
    m_world.add_physics_law(Law::gravitation);
}

void GameState::init_factory() {
    m_factory.register_entity("small_circle", [&]() {
        auto entity = m_world.create_entity();
        auto position = sf::Vector2f{random(0.f, 1280.f), random(0.f, 720.f)};
        auto circle = std::make_shared<Circle>(random(5.f, 15.f));

        PhysicsBody::Ptr physics_c = std::make_unique<PhysicsBody>(circle, position, Data::steel);
        m_world.physics().add_body(physics_c);
        entity->add_component<PhysicsBody>(physics_c);

        auto circle_c = std::make_unique<DrawableCircle>(50.f);
        circle_c->set_texture(Locator::locate<ResourceControl>().texture()[Textures::blue_star]);
        entity->add_component(circle_c);
        return entity;
    });

    m_factory.register_entity("huge_circle", [&]() {
        auto entity = m_world.create_entity();
        auto circle = std::make_shared<Circle>(80.f);
        PhysicsBody::Ptr physics_c = std::make_unique<PhysicsBody>(circle, sf::Vector2f{500.f, 300.f},
                                                                   Data::super_solid);
        m_world.physics().add_body(physics_c);
        entity->add_component<PhysicsBody>(physics_c);

//            auto circle_c = std::make_unique<DrawableCircle>(50.f);
//            circle_c->set_texture(Locator::locate<ResourceControl>().texture()[Textures::circle_earth]);
//            entity->add_component(circle_c);
        return entity;
    });
}
