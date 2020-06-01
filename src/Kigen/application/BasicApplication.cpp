//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 25.02.19.
//

#include "Kigen/application/BasicApplication.hpp"

namespace kigen {

BasicApplication::BasicApplication(): m_window(sf::VideoMode(1280, 720), "TEST") {
    m_window.setFramerateLimit(60);

    m_rtexture.create(1280, 720);
    m_rtexture.setSmooth(true);
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
    m_canvas.setTexture(m_rtexture.getTexture());

    m_rtexture.clear();
    m_state_control.draw(m_rtexture);
}

void kigen::BasicApplication::render() {
    m_rtexture.display();

    m_window.clear();
    m_window.draw(m_canvas);
    m_window.display();
}

} // namespace kigen