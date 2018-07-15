//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#include "Yosai/States/MenuState.hpp"


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
    return false;
}

bool MenuState::handleEvent(const sf::Event &event) {
    return false;
}
