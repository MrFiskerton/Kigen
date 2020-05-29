//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.05.2020.
//

#include <SFML/Graphics/CircleShape.hpp>
#include "Yosai/states/GameState.hpp"

using namespace kigen;

GameState::GameState(StateControl &stack) : State(stack) {

}

GameState::~GameState() {}

void GameState::draw(sf::RenderTarget &target) {
    sf::CircleShape shape(100.f);

    shape.setTexture(&Locator::locate<ResourceControl>().texture()[Textures::water]);
    //shape.setFillColor(sf::Color::Green);

    target.draw(shape);
}

bool GameState::update(const sf::Time &delta) {
    return false;
}

bool GameState::handleEvent(const sf::Event &event) {
    return false;
}
