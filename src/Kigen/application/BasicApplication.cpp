//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 25.02.19.
//

#include "Kigen/application/BasicApplication.hpp"

namespace kigen {

BasicApplication::BasicApplication(): m_window(sf::VideoMode(500, 500), "TEST") {
    init_services();
}

bool kigen::BasicApplication::is_runing() const {
    return m_window.isOpen() && !m_state_control.isEmpty();
}

void kigen::BasicApplication::update_input() {
    m_input.update(m_window);
}

void kigen::BasicApplication::update_logic(const sf::Time &deltaTime) {
    m_state_control.update(deltaTime);
}

void kigen::BasicApplication::update_graphics() {
    m_canvas.setTexture(m_renderTexture.getTexture());

    m_renderTexture.clear();
    m_state_control.draw(m_renderTexture);
    m_renderTexture.display();
}

void kigen::BasicApplication::render() {
    m_window.clear();
    m_window.draw(m_canvas);
    m_window.display();
}

void BasicApplication::init_services() {
    Locator::registrate<InputControl>();
    Locator::provide<InputControl>(&m_input);

    Locator::registrate<ResourceControl>();
    Locator::provide<ResourceControl>(&m_resources);
}

} // namespace kigen