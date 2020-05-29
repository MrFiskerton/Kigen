//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.05.2020.
//

#include "Yosai/states/GameState.hpp"

GameState::GameState(StateControl &stack) : State(stack) {

}

GameState::~GameState() {}

void GameState::draw(sf::RenderTarget &renderTarget) {

}

bool GameState::update(const sf::Time &deltaTime) {
    return false;
}

bool GameState::handleEvent(const sf::Event &event) {
    return false;
}
