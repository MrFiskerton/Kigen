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
public:
    enum ActionType : unsigned char {
        RealTime = 1u,
        Pressed  = unsigned char(1) << 1,
        Released = unsigned char(1) << 2
    };
public:
    KeyboardController();

    virtual ~KeyboardController();

    void update() override;
    void handle_event(const sf::Event &event) override;
    bool test(sf::Keyboard::Key key, unsigned char type = ActionType::RealTime | ActionType::Pressed) const;

    void start_reading_text();
    void stop_reading_text();
    const std::string& get_read_text() const;
    void crop_read_text(std::size_t maxLength);

    void setVirtualKeyboardVisible(bool visible); // Only for mobile version

protected:
    void read_unicode(sf::Uint32 character);

private:
    std::multimap<sf::Keyboard::Key, ActionType> m_event_buffer;

    bool is_reading;
    std::string m_text;
};

#endif //INCLUDED_KEYBOARDCONTROLLER_HPP
