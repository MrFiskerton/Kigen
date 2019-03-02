//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 25.02.19.
//

#include "Kigen/application/BasicApplication.hpp"

namespace kigen {

BasicApplication::BasicApplication() {
    init_services();
    init_action();
}

bool kigen::BasicApplication::is_runing() const {
    return m_window.isOpen() && !m_state_control.isEmpty();
}

void kigen::BasicApplication::update_input() {
    m_action.update(m_window);
}

void kigen::BasicApplication::update_logic(const sf::Time &deltaTime) {
    m_state_control.update(deltaTime);
    m_action.invoke_callbacks(m_callbaks);
}

void kigen::BasicApplication::update_graphics() {

}

void kigen::BasicApplication::render() {

}

void BasicApplication::init_services() {
    Locator::registrate<ICamera>();

    Locator::locate<ICamera>().test();

    Camera camera;
    Locator::provide<ICamera>(&camera);
    Locator::locate<ICamera>().test();

    Locator::provide<ICamera>(nullptr);
    Locator::locate<ICamera>().test();
}

void BasicApplication::init_action() {
    m_action["Up"] = Action(sf::Keyboard::W, RealTime | Pressed);
    m_action["Down"] = Action(sf::Keyboard::S, RealTime | Pressed);
    m_action["Left"] = Action(sf::Keyboard::A, RealTime | Pressed);
    m_action["Right"] = Action(sf::Keyboard::D, RealTime | Pressed);

    m_callbaks["Up"] = []() { Logger::notify("Up"); };
    m_callbaks["Down"] = []() { Logger::notify("Down"); };
    m_callbaks["Left"] = []() { Logger::notify("Left"); };
    m_callbaks["Right"] = []() { Logger::notify("Right"); };
}

} // namespace kigen