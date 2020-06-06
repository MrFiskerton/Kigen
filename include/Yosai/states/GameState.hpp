//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.05.2020.
//

#ifndef YOSAI_GAMESTATE_HPP
#define YOSAI_GAMESTATE_HPP

#include <Kigen/world/physics/shape/Polygon.hpp>
#include <Kigen/state/State.hpp>
#include <Kigen/world/World.hpp>
#include <Yosai/models/Materials.hpp>
#include <Kigen/world/component/DrawableDebugBody.hpp>
#include <Kigen/utils/Random.hpp>

using namespace kigen;

class GameState : public State {

public:
    explicit GameState(StateControl &stack);
    ~GameState() override;

    void draw(sf::RenderTarget& target) override;
    bool update(const sf::Time& delta) override;
    bool handleEvent(const sf::Event &event) override;

private:
    Entity::Ptr create_entity(sf::Vector2f position, int t);

private:
    World m_world;

};


#endif //YOSAI_GAMESTATE_HPP
