//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#include "Yosai/states/MenuState.hpp"


MenuState::MenuState(StateControl &stack) : State(stack) {}

MenuState::~MenuState() {

}

#include <SFML/Graphics.hpp>
void MenuState::draw(sf::RenderTarget &renderTarget) {
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    renderTarget.draw(shape);
}

bool MenuState::update(const sf::Time &deltaTime) {
    requestStackPush(States::ID::Game);
    return false;
}

bool MenuState::handleEvent(const sf::Event &event) {
    return false;
}
