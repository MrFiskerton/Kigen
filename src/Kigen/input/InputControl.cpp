//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#include <Kigen/input/InputControl.hpp>
#include <Kigen/action/detail/ActionLeaves.hpp>

namespace kigen {

void InputControl::update(sf::Window &window) {
    if (!is_enabled()) return;
    clear();
    poll_events(window);
    m_mouse.update_position(window);
}

void InputControl::clear() {
    m_window.clear();
    m_keyboard.clear();
    m_mouse.clear();
    m_buffer.clear();
}

void InputControl::push(const sf::Event &event) {
    get_compatible_device(event).push(event);
    m_buffer.push_back(event);
}

void InputControl::poll_events(sf::Window &window) {
    static sf::Event event;
    while (window.pollEvent(event)) push(event);
}

device::AbstractDevice &InputControl::get_compatible_device(const sf::Event &event) {
#   define IF_EVENT_IN_INTERVAL(L, R)\
    if(static_cast<int>(sf::Event::EventType::L) <= static_cast<int>(event.type) && \
                                                    static_cast<int>(event.type) <= static_cast<int>(sf::Event::EventType::R))
//--------------------------------------------------------------------------------------------------------------------//

    IF_EVENT_IN_INTERVAL(Closed, GainedFocus) return m_window;
    IF_EVENT_IN_INTERVAL(TextEntered, KeyReleased) return m_keyboard;
    IF_EVENT_IN_INTERVAL(MouseWheelMoved, MouseLeft) return m_mouse;
    // IF_EVENT_IN_INTERVAL(JoystickButtonPressed, JoystickDisconnected) return AbstractDevice::Joystick;
    // TouchBegan, TouchMoved, TouchEnded, SensorChanged, Count
#   undef IF_EVENT_IN_INTERVAL
    Logger::warn("InputControl::get_compatible_device",
                 "Passed not compatible event sf::Event::EventType::" + conversion::to_string(event.type));
    return m_null;
}

device::WindowStatus &InputControl::window() { return m_window; }

device::Keyboard &InputControl::keyboard() { return m_keyboard; }

device::Mouse &InputControl::mouse() { return m_mouse; }

} //namespace kigen