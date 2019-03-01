//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#include <Kigen/input/EventBuffer.hpp>

namespace kigen {

void EventBuffer::enable_device(Device device) {
    switch (device) {
        case Window: device::Window::enable();
            break;
        case Keyboard: device::Keyboard::enable();
            break;
        case Mouse: device::Mouse::enable();
            break; //TODO:
        case Joystick:break;
        case All:device::Window::enable();
            device::Keyboard::enable();
            device::Mouse::enable();
            break;
        case Unknown:break;
    }
}

void EventBuffer::disable_device(Device device) {
    switch (device) {
        case Window: device::Window::disable();
            break;
        case Keyboard: device::Keyboard::disable();
            break;
        case Mouse: device::Mouse::disable();
            break;
        case Joystick:break;
        case All:
            device::Window::disable();
            device::Keyboard::disable();
            device::Mouse::disable();
            break;
        case Unknown:break;
    }
}

bool EventBuffer::is_disabled(Device device) const {
    return !is_enabled(device);
}

bool EventBuffer::is_enabled(Device device) const {
    switch (device) {
        case Window: return device::Window::is_enabled();
        case Keyboard: return device::Keyboard::is_enabled();
        case Mouse: return device::Mouse::is_enabled();
        case Joystick:break;
        case All:
            return device::Window::is_enabled() &&
                   device::Keyboard::is_enabled() &&
                   device::Mouse::is_enabled();

        case Unknown:break;
    }
    return false;
}

void EventBuffer::update(sf::Window &window) {
    if (is_disabled(All)) return;
    clear_events();
    poll_events(window);
    device::Mouse::update_position(window);
}

void EventBuffer::clear_events() {
    device::Window::clear_events();
    device::Keyboard::clear_events();
    device::Mouse::clear_events();
}

void EventBuffer::handle_event(const sf::Event &event) {
    switch (get_compatible_device(event)) {
        case Unknown:
            Logger::warn("input::handle_event", "Passed not compatible event sf::Event::EventType::"
                                                + conversion::to_string(event.type));
            break;
        case Window:device::Window::handle_event(event);
            break;
        case Keyboard:device::Keyboard::handle_event(event);
            break;
        case Mouse:device::Mouse::handle_event(event);
            break;
            //case Joystick:break;
            //case All:break;
        case Joystick:break;
        case All:break;
    }

}

void EventBuffer::poll_events(sf::Window &window) {
    static sf::Event event;
    while (window.pollEvent(event)) handle_event(event);
}

EventBuffer::Device EventBuffer::get_compatible_device(const sf::Event &event) {
#   define IF_EVENT_IN_INTERVAL(L, R)\
    if(static_cast<int>(sf::Event::EventType::L) <= static_cast<int>(event.type) && \
                                                    static_cast<int>(event.type) <= static_cast<int>(sf::Event::EventType::R))

    IF_EVENT_IN_INTERVAL(Closed, GainedFocus) return Device::Window;
    IF_EVENT_IN_INTERVAL(TextEntered, KeyReleased) return Device::Keyboard;
    IF_EVENT_IN_INTERVAL(MouseWheelMoved, MouseLeft) return Device::Mouse;
    // IF_EVENT_IN_INTERVAL(JoystickButtonPressed, JoystickDisconnected) return Device::Joystick;
    // TouchBegan, TouchMoved, TouchEnded, SensorChanged, Count
#   undef IF_EVENT_IN_INTERVAL
    return Device::Unknown;
}

}