//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#include "Yosai/InputControl/InputControl.hpp"

void InputControl::lock_action(Device device) {
    switch (device){
        case Non:break;
        case Keyboard: KeyboardController::lock_action();
        case Mouse:break;
        case All:break;
        case Count:break;
    }
}

void InputControl::unlock_action(Device device) {
    switch (device){
        case Non:break;
        case Keyboard: KeyboardController::unlock_action();
        case Mouse:break;
        case All:break;
        case Count:break;
    }
}

bool InputControl::is_locked(Device device) const {
    switch (device){
        case Non:break;
        case Keyboard: return KeyboardController::is_locked();
        case Mouse:break;
        case All:break;
        case Count:break;
    }

    return false;
}

void InputControl::clear_event_buffer() {
    m_buffer.clear();
    KeyboardController::clear_event_buffer();
}

void InputControl::handle_event(const sf::Event &event) {
    m_buffer.push(event);
    switch (event.type){
        // Window
        case sf::Event::Closed:
        case sf::Event::Resized:
        case sf::Event::LostFocus:
        case sf::Event::GainedFocus:
            Logger::warn("InputControl::handle_event", "Window event sf::Event::" + Conversion::to_string(event.type));
            break;

        // Keyboard
        case sf::Event::TextEntered:
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
            KeyboardController::handle_event(event);
            break;

        // Mouse
        case sf::Event::MouseWheelMoved:
        case sf::Event::MouseWheelScrolled:
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        case sf::Event::MouseMoved:
        case sf::Event::MouseEntered:
        case sf::Event::MouseLeft:
            break;

        // Joystick
        case sf::Event::JoystickButtonPressed:
        case sf::Event::JoystickButtonReleased:
        case sf::Event::JoystickMoved:
        case sf::Event::JoystickConnected:
        case sf::Event::JoystickDisconnected:
            Logger::warn("InputControl::handle_event", "Joystick event sf::Event::" + Conversion::to_string(event.type));
            break;

        /*// Sensor
        case sf::Event::TouchBegan:break;
        case sf::Event::TouchMoved:break;
        case sf::Event::TouchEnded:break;
        case sf::Event::SensorChanged:break;*/

        // Meta information
        case sf::Event::Count:break;
        default: Logger::warn("InputControl::handle_event", "Passed not compatible event sf::Event::" + Conversion::to_string(event.type));
    }
}

void InputControl::poll_events(sf::Window &window) {
    clear_event_buffer();

    static sf::Event event;
    while (window.pollEvent(event)) handle_event(event);
}
