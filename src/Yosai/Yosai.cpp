//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 23.02.19.
//

#include "Yosai/Yosai.hpp"

Yosai::Yosai() {
    init_state_control();
}

void Yosai::init_state_control() {
    m_state_control.registerState<MenuState>(States::ID::Menu);
    m_state_control.forcePushState(States::ID::Menu);
}

