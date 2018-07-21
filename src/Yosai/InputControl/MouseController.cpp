//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#include "Yosai/InputControl/MouseController.hpp"

MouseController::MouseController() {

}

MouseController::~MouseController() {

}

void MouseController::clear_events() {
    // Update mouse wheel
    m_mouseWheelScrollTicks = 0.f;

    // Update mouse clicks
    m_event_buffer.clear();

    // Update mouse positions
    if (m_isMouseMoved) {
        // TODO: Mouse position
    }
    m_isMouseMoved = false;
}

void MouseController::handle_event(const sf::Event &event) {
    if (is_locked()) return;

    switch (event.type) {
        //case sf::Event::MouseWheelMoved:break; (deprecated)
        case sf::Event::MouseWheelScrolled:m_mouseWheelScrollTicks = event.mouseWheelScroll.delta;break; // Можно получить x, y ?

        case sf::Event::MouseButtonPressed:  m_event_buffer.emplace(event.mouseButton.button, Pressed);break;
        case sf::Event::MouseButtonReleased: m_event_buffer.emplace(event.mouseButton.button, Clicked);break;

        case sf::Event::MouseMoved:   m_isMouseMoved      = true;  break;
        case sf::Event::MouseEntered: m_isMouseInsideView = true;  break;
        case sf::Event::MouseLeft:    m_isMouseInsideView = false; break;

        default: Logger::warn("MouseController::handle_event", "Passed not compatible event");
    }
}

void MouseController::set_window(sf::RenderWindow *window) {
    m_window = window;
}

bool MouseController::isMouseInsedeView() {
    return m_isMouseInsideView;
}

bool MouseController::isMouseMoved() {
    return m_isMouseMoved;
}

bool MouseController::isMouseOver(const sf::FloatRect &boundingBox, bool useDefaultView) const {
    return boundingBox.contains(getMousePosition(useDefaultView));
}

bool MouseController::isMouseWheelScrolledDown() const {
    return !is_locked() && m_mouseWheelScrollTicks < 0.f;
}

bool MouseController::isMouseWheelScrolledUp() const {
    return !is_locked() && m_mouseWheelScrollTicks > 0.f;;
}

const sf::Vector2f &MouseController::getMousePosition(bool useDefaultView) const {
    return (useDefaultView ? m_defaultViewMousePosition : m_mousePosition);
}

bool MouseController::test(sf::Mouse::Button button, MouseActionType action) const {
    if (is_locked()) return false;

    if (action == Hold) {
        return sf::Mouse::isButtonPressed(button);
    } else {
        auto range = m_event_buffer.equal_range(button);
        for (auto it = range.first; it != range.second; it++) {
            if (action == it->second) return true;
        }
    }

    return false;
}

bool MouseController::test(sf::Mouse::Button button, MouseActionType action,
                           const sf::FloatRect &boundingBox, bool useDefaultView) const {
    return test(button, action) && isMouseOver(boundingBox, useDefaultView);
}
