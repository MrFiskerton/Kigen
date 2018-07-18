//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_KEYBOARDCONTROLLER_HPP
#define INCLUDED_KEYBOARDCONTROLLER_HPP

#include <map>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "AbstractDeviceController.hpp"

class KeyboardController: public AbstractDeviceController {
private:
    enum KeyboardActionType : unsigned char {
        RealTime = 1u,
        Pressed  = 1u << 1,
        Released = 1u << 2
    };
public:
    KeyboardController();

    virtual ~KeyboardController();

    void clear_event_buffer() override;
    void handle_event(const sf::Event &event) override;
    sf::Keyboard::Key lastPressedKey() const;

    // Realtime
    bool isKeyPressed(sf::Keyboard::Key key);
    bool isKeyReleased(sf::Keyboard::Key key);
    // According to event
    bool isKeyJustPressed (sf::Keyboard::Key key);
    bool isKeyJustReleased(sf::Keyboard::Key key);

    void start_reading_text();
    void stop_reading_text();
    const std::string& get_read_text() const;
    void crop_read_text(std::size_t maxLength);

    void setVirtualKeyboardVisible(bool visible); // Only for mobile version

private:
    void read_unicode(sf::Uint32 character);
    bool test(sf::Keyboard::Key key, unsigned char type) const;
private:
    std::multimap<sf::Keyboard::Key, KeyboardActionType> m_event_buffer;

    sf::Keyboard::Key m_last_pressed_key; // TODO: store last 3 key pressed. Usage: keybind screen

    bool is_reading;
    std::string m_text;
};

#endif //INCLUDED_KEYBOARDCONTROLLER_HPP
