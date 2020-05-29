//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#include <Kigen/input/Mouse.hpp>

namespace kigen {
namespace device {

void Mouse::clear() {
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

void Mouse::push(const sf::Event &event) {
    if (!is_enabled()) return;

    switch (event.type) {
        //case sf::Event::MouseWheelMoved:break; (deprecated)
        case sf::Event::MouseWheelScrolled:m_mouseWheelScrollTicks = event.mouseWheelScroll.delta;
            break; // Можно получить x, y ?

        case sf::Event::MouseButtonPressed:m_event_buffer.emplace(event.mouseButton.button, Pressed);
            break;
        case sf::Event::MouseButtonReleased:m_event_buffer.emplace(event.mouseButton.button, Clicked);
            break;

        case sf::Event::MouseMoved:m_isMouseMoved = true;
            break;
        case sf::Event::MouseEntered:m_isMouseInsideView = true;
            break;
        case sf::Event::MouseLeft:m_isMouseInsideView = false;
            break;

        default:Logger::warn("Mouse::push", "Passed not compatible event");
    }
}

void Mouse::update_position(const sf::Window &window) {
    //sf::Mouse::getPosition(); //Absolute coordinates
    //m_mousePosition = sf::Mouse::getPosition(window); //Relative to window //TODO
}

bool Mouse::isMouseInsideView() {
    return m_isMouseInsideView;
}

bool Mouse::isMouseMoved() {
    return m_isMouseMoved;
}

bool Mouse::isMouseOver(const sf::FloatRect &boundingBox, bool useDefaultView) const {
    return boundingBox.contains(getMousePosition(useDefaultView));
}

bool Mouse::isMouseWheelScrolledDown() const {
    return is_enabled() && m_mouseWheelScrollTicks < 0.f;
}

bool Mouse::isMouseWheelScrolledUp() const {
    return is_enabled() && m_mouseWheelScrollTicks > 0.f;;
}

const sf::Vector2f &Mouse::getMousePosition(bool useDefaultView) const {
    return (useDefaultView ? m_defaultViewMousePosition : m_mousePosition);
}

bool Mouse::test(sf::Mouse::Button button, MouseActionType action) const {
    if (!is_enabled()) return false;

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

bool Mouse::test(sf::Mouse::Button button, MouseActionType action,
                 const sf::FloatRect &boundingBox, bool useDefaultView) const {
    return test(button, action) && isMouseOver(boundingBox, useDefaultView);
}


} //namespace device
} //namespace kigen