//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#include "Yosai/InputControl/MouseController.hpp"

MouseController::MouseController() {

}

MouseController::~MouseController() {

}

void MouseController::update() {

}

void MouseController::handle_event(const sf::Event &event) {
    if(is_locked()) return;

    switch (event.type) {
        case sf::Event::MouseWheelMoved:break;
        case sf::Event::MouseWheelScrolled:break;
        case sf::Event::MouseButtonPressed:break;
        case sf::Event::MouseButtonReleased:break;
        case sf::Event::MouseMoved:break;
        case sf::Event::MouseEntered:break;
        case sf::Event::MouseLeft:break;
        default: Logger::warn("MouseController::handle_event", "Passed not compatible event");
    }
}

void MouseController::set_window(sf::RenderWindow *window) {
    m_window = window;
}

