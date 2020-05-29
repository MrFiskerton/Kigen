//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 21.07.18.
//

#include <Kigen/input/WindowStatus.hpp>

namespace kigen {
namespace device {

void WindowStatus::clear() {
    m_closed = m_resized = m_lostFocus = m_gainedFocus = false;
}

void WindowStatus::push(const sf::Event &event) {
    if (!is_enabled()) return;

    switch (event.type) {
        case sf::Event::Closed:      m_closed = true;      break;
        case sf::Event::Resized:     m_resized = true;     break;
        case sf::Event::LostFocus:   m_lostFocus = true;   break;
        case sf::Event::GainedFocus: m_gainedFocus = true; break;
        default:
            Logger::warn("WindowStatus::push", "Passed not compatible event");
    }
}

bool WindowStatus::isClosed() { return m_closed; }

bool WindowStatus::isResized() { return m_resized; }

bool WindowStatus::isGainedFocus() { return m_gainedFocus; }

bool WindowStatus::isLostFocus() { return m_lostFocus; }

} //namespace device
} //namespace kigen



