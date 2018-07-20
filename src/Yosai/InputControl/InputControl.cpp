//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#include "Yosai/InputControl/InputControl.hpp"

void InputControl::lock_action(Device device) {
    switch (device) {
        //case Unknown:break;
        // TODO:
        case Window:break;
        case Keyboard: KeyboardController::lock_action();break;
        case Mouse:break;
        case Joystick:break;
        case All:break;
    }
}

void InputControl::unlock_action(Device device) {
//TODO:
}

bool InputControl::is_locked(Device device) const {
    //TODO:
    return false;
}

void InputControl::update() {
    m_buffer.clear();
    KeyboardController::update();
    MouseController::update();
}

void InputControl::handle_event(const sf::Event &event) {
    m_buffer.push(event);
    switch (get_compatible_device(event)) {
        case Unknown: Logger::warn("InputControl::handle_event", "Passed not compatible event sf::Event::EventType::"
                                                                 + Conversion::to_string(event.type));break;
        case Window:break;
        case Keyboard: KeyboardController::handle_event(event); break;
        case Mouse:    MouseController::handle_event(event);    break;
        case Joystick:break;
        //case All:break;
    }

}

void InputControl::poll_events(sf::Window &window) {
    update();

    static sf::Event event;
    while (window.pollEvent(event)) handle_event(event);
}

InputControl::Device InputControl::get_compatible_device(const sf::Event &event) {
#   define IF_EVENT_IN_INTERVAL(L, R)\
    if(static_cast<int>(sf::Event::EventType::L) <= static_cast<int>(event.type) && \
                                                    static_cast<int>(event.type) <= static_cast<int>(sf::Event::EventType::R))

    //IF_EVENT_IN_INTERVAL(Closed, GainedFocus) return Device::Window;
    IF_EVENT_IN_INTERVAL(TextEntered, KeyReleased) return Device::Keyboard;
    IF_EVENT_IN_INTERVAL(MouseWheelMoved, MouseLeft) return Device::Mouse;
    IF_EVENT_IN_INTERVAL(JoystickButtonPressed, JoystickDisconnected) return Device::Joystick;
    // TouchBegan, TouchMoved, TouchEnded, SensorChanged, Count
#   undef IF_EVENT_IN_INTERVAL
    return Device::Unknown;
}
