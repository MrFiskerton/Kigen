//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 21.07.18.
//

#include <Kigen/input/Window.hpp>

namespace kigen {
namespace device {

void Window::clear_events() {
    m_closed = m_resized = m_lostFocus = m_gainedFocus = false;
}

void Window::handle_event(const sf::Event &event) {
    if (is_disabled()) return;

    switch (event.type) {
        case sf::Event::Closed:      m_closed = true;      break;
        case sf::Event::Resized:     m_resized = true;     break;
        case sf::Event::LostFocus:   m_lostFocus = true;   break;
        case sf::Event::GainedFocus: m_gainedFocus = true; break;
        default:
            Logger::warn("Window::handle_event", "Passed not compatible event");
    }
}

bool Window::isClosed() { return m_closed; }

bool Window::isResized() { return m_resized; }

bool Window::isGainedFocus() { return m_gainedFocus; }

bool Window::isLostFocus() { return m_lostFocus; }

} //namespace device
} //namespace kigen



