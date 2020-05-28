//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 23.02.19.
//

#include "Yosai/Yosai.hpp"

using namespace kigen;
using namespace Actions;

Yosai::Yosai() {
    //init_services();
    init_actions();
    init_state_control();
}

void Yosai::init_state_control() {
    m_state_control.registerState<MenuState>(States::ID::Menu);
    m_state_control.registerState<GameState>(States::ID::Game);

    m_state_control.forcePushState(States::ID::Game);
}

void Yosai::init_actions() {
    auto &registry = m_actions.get_registry();

    registry[close_window] = Action(sf::Keyboard::Escape, Released)
                          || Action([&]() { return m_input.window().isClosed(); });

    m_actions.connect(close_window, [&]() { m_window.close(); });
}

//void Yosai::init_services() {
//    Locator::registrate<ActionControl<ID>>();
//    Locator::provide<ActionControl<ID>>(&m_actions);
//}

void Yosai::update_logic(const sf::Time &delta) {
    m_actions.invoke_callbacks();
    BasicApplication::update_logic(delta);
}
