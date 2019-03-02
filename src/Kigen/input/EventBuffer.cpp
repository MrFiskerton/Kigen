//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#include <Kigen/input/EventBuffer.hpp>
#include <Kigen/action/detail/EventNode.hpp>

namespace kigen {

void EventBuffer::update(sf::Window &window) {
    if (is_disabled()) return;
    clear();
    poll_events(window);
    m_mouse.update_position(window);
}

void EventBuffer::clear() {
    m_window.clear();
    m_keyboard.clear();
    m_mouse.clear();
    m_buffer.clear();
}

void EventBuffer::push(const sf::Event &event) {
    get_compatible_device(event).push(event);
    m_buffer.push_back(event);
}

void EventBuffer::poll_events(sf::Window &window) {
    static sf::Event event;
    while (window.pollEvent(event)) push(event);
}

device::DeviceBuffer &EventBuffer::get_compatible_device(const sf::Event &event) {
#   define IF_EVENT_IN_INTERVAL(L, R)\
    if(static_cast<int>(sf::Event::EventType::L) <= static_cast<int>(event.type) && \
                                                    static_cast<int>(event.type) <= static_cast<int>(sf::Event::EventType::R))
//--------------------------------------------------------------------------------------------------------------------//

    IF_EVENT_IN_INTERVAL(Closed, GainedFocus) return m_window;
    IF_EVENT_IN_INTERVAL(TextEntered, KeyReleased) return m_keyboard;
    IF_EVENT_IN_INTERVAL(MouseWheelMoved, MouseLeft) return m_mouse;
    // IF_EVENT_IN_INTERVAL(JoystickButtonPressed, JoystickDisconnected) return Device::Joystick;
    // TouchBegan, TouchMoved, TouchEnded, SensorChanged, Count
#   undef IF_EVENT_IN_INTERVAL
    Logger::warn("EventBuffer::get_compatible_device",
                 "Passed not compatible event sf::Event::EventType::" + conversion::to_string(event.type));
    return m_null;
}

device::Window &EventBuffer::window() { return m_window; }

device::Keyboard &EventBuffer::keyboard() { return m_keyboard; }

device::Mouse &EventBuffer::mouse() { return m_mouse; }

bool EventBuffer::contains(const action::EventNode &node) const {
    /*
     * Note: Since there are at most a few dozens of events per frame (at a decent framerate not even that), std::vector and linear search is fine.
     */
    for (auto &event: m_buffer) if (node.isEventActive(event)) return true;
    return false;
}

} //namespace kigen