//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#include "Yosai/InputControl/KeyboardController.hpp"

KeyboardController::KeyboardController(): m_event_buffer(), is_reading(false), m_text() {}

KeyboardController::~KeyboardController() {

}

void KeyboardController::update() {
    m_event_buffer.clear();
}

void KeyboardController::handle_event(const sf::Event &event) {
    if (AbstractDeviceController::is_locked()) return;

    switch (event.type){
        case sf::Event::TextEntered: read_unicode(event.text.unicode); break;
        case sf::Event::KeyPressed:  m_event_buffer.emplace(event.key.code, Pressed);  break;
        case sf::Event::KeyReleased: m_event_buffer.emplace(event.key.code, Released); break;

        default: Logger::warn("KeyboardController::handle_event", "Passed not compatible event");
    }
}

bool KeyboardController::test(sf::Keyboard::Key key, unsigned char type) const {
    if (is_locked()) return false;

    if (type & RealTime) {
        bool is_pressed = sf::Keyboard::isKeyPressed(key);
        bool expect_pressed = (type & Pressed);

        if(is_pressed == expect_pressed) return true; //XNOR
    } else {
        auto range = m_event_buffer.equal_range(key);
        for(auto it = range.first; it != range.second; it++) {
            if (type & it->second) return true;
        }
    }
    return false;
}

void KeyboardController::start_reading_text() {
    is_reading = true;
}

void KeyboardController::stop_reading_text() {
    is_reading = false;
    m_text.clear();
}

const std::string &KeyboardController::get_read_text() const {
    return m_text;
}

void KeyboardController::crop_read_text(std::size_t maxLength) {
    m_text = m_text.substr(0, maxLength);
}

void KeyboardController::read_unicode(sf::Uint32 character) {
    if (!is_reading) return;
    if (character == '\t' || character == '\n' || character == '\r') return;

    if (character == '\b') {
        if (!m_text.empty()) m_text.erase(m_text.size() - 1, 1);
    } else if (character < 128) { // ASCII character
        m_text += static_cast<char>(character);
    }
}

void KeyboardController::setVirtualKeyboardVisible(bool visible) {
    if (is_locked()) return;
    sf::Keyboard::setVirtualKeyboardVisible(visible);
}

