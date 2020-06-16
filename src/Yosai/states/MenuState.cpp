//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#include "Yosai/states/MenuState.hpp"


MenuState::MenuState(StateControl &stack) : State(stack) {}

MenuState::~MenuState() {

}

#include <SFML/Graphics.hpp>
void MenuState::draw(sf::RenderTarget &target) {

}

bool MenuState::update(const sf::Time &delta) {
    requestStackPush(States::ID::Game);
    return false;
}

bool MenuState::handleEvent(const sf::Event &event) {
    return false;
}
