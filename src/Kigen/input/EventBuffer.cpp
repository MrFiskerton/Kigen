//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#include <Kigen/input/EventBuffer.hpp>

namespace kigen {

void EventBuffer::lock_device(Device device) {
    switch (device) {
        //case Unknown:break;
        // TODO:
        case Window: break;
        case Keyboard: Keyboard::disable();
            break;
        case Mouse:break;
        case Joystick:break;
        case All:break;
    }
}

void EventBuffer::unlock_device(Device device) {
//TODO:
}

bool EventBuffer::is_locked(Device device) const {
    //TODO:
    return false;
}

void EventBuffer::update(sf::Window &window) {
    if (is_locked(All)) return;
    clear_events();
    poll_events(window);
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