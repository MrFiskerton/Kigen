//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 21.07.18.
//

#include "Yosai/InputControl/WindowController.hpp"

WindowController::WindowController() {}

WindowController::~WindowController() {

}

void WindowController::clear_events() {
    m_closed = m_resized = m_lostFocus = m_gainedFocus = false;
}

void WindowController::handle_event(const sf::Event &event) {
    if(is_locked()) return;

    switch (event.type) {
        case sf::Event::Closed:      m_closed      = true; break;
        case sf::Event::Resized:     m_resized     = true; break;
        case sf::Event::LostFocus:   m_lostFocus   = true; break;
        case sf::Event::GainedFocus: m_gainedFocus = true; break;

        default: Logger::warn("WindowController::handle_event", "Passed not compatible event");
    }
}

bool WindowController::isClosed() {
    return m_closed;
}

bool WindowController::isResized() {
    return m_resized;
}

bool WindowController::isGainedFocus() {
    return m_gainedFocus;
}

bool WindowController::isLostFocus() {
    return m_lostFocus;
}




