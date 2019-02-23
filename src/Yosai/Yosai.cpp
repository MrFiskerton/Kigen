//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 23.02.19.
//

#include "Yosai/Yosai.hpp"

Yosai::Yosai() {
    init_state_control();
}

bool Yosai::is_runing() {
    return m_renderWindow.isOpen() && !m_stateControl.isEmpty();
}

void Yosai::update_input() {

}

void Yosai::update_logic(const sf::Time &deltaTime) {
    m_stateControl.update(deltaTime);
}

void Yosai::update_graphics() {

}

void Yosai::render() {

}

void Yosai::init_state_control() {
    m_stateControl.registerState<MenuState>(States::ID::Menu);
    m_stateControl.forcePushState(States::ID::Menu);
}

void Yosai::init_services() {

}
