//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#include <Kigen/input/Keyboard.hpp>

namespace kigen {
namespace device {

Keyboard::Keyboard() : m_event_buffer(), is_reading(false), m_text(), m_last_pressed_key(sf::Keyboard::Key::Unknown) {}

void Keyboard::clear() {
    m_last_pressed_key = sf::Keyboard::Unknown;
    m_event_buffer.clear();
}

void Keyboard::push(const sf::Event &event) {
    if (DeviceBuffer::is_disabled()) return;

    switch (event.type) {
        case sf::Event::TextEntered:read_unicode(event.text.unicode);
            break;
        case sf::Event::KeyPressed:m_last_pressed_key = event.key.code;
            m_event_buffer.emplace(event.key.code, Pressed);
            break;
        case sf::Event::KeyReleased:m_event_buffer.emplace(event.key.code, Released);
            break;

        default:
            Logger::warn("Keyboard::push",
                         "Passed not compatible event sf::Event::" + conversion::to_string(event.type));
    }
}

sf::Keyboard::Key Keyboard::lastPressedKey() const {
    return m_last_pressed_key;
}

bool Keyboard::test(sf::Keyboard::Key key, unsigned char type) const {
    if (is_disabled()) return false;

    if (type & RealTime) {
        bool is_pressed = sf::Keyboard::isKeyPressed(key);
        bool expect_pressed = (type & Pressed);

        if (is_pressed == expect_pressed) return true; //XNOR
    } else {
        auto range = m_event_buffer.equal_range(key);
        for (auto it = range.first; it != range.second; it++) {
            if (type & it->second) return true;
        }
    }
    return false;
}

bool Keyboard::isKeyPressed(sf::Keyboard::Key key) {
    return test(key, RealTime | Pressed);
}

bool Keyboard::isKeyReleased(sf::Keyboard::Key key) {
    return test(key, RealTime | Released);
}

bool Keyboard::isKeyJustPressed(sf::Keyboard::Key key) {
    return test(key, Pressed);
}

bool Keyboard::isKeyJustReleased(sf::Keyboard::Key key) {
    return test(key, Released);
}

void Keyboard::start_reading_text() {
    is_reading = true;
}

void Keyboard::stop_reading_text() {
    is_reading = false;
    m_text.clear();
}

const std::string &Keyboard::get_read_text() const {
    return m_text;
}

void Keyboard::crop_read_text(std::size_t maxLength) {
    m_text = m_text.substr(0, maxLength);
}

void Keyboard::read_unicode(sf::Uint32 character) {
    if (!is_reading) return;
    if (character == '\t' || character == '\n' || character == '\r') return;

    if (character == '\b') {
        if (!m_text.empty()) m_text.erase(m_text.size() - 1, 1);
    } else if (character < 128) { // ASCII character
        m_text += static_cast<char>(character);
    }
}

void Keyboard::setVirtualKeyboardVisible(bool visibility) {
    if (is_disabled()) return;
    sf::Keyboard::setVirtualKeyboardVisible(visibility);
}

} //namecpace device
} //namespace kigen