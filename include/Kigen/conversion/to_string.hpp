//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 19.07.18.
//

#ifndef INCLUDED_CONVERSION_HPP
#define INCLUDED_CONVERSION_HPP


#include <string>
#include <map>

#include <SFML/Window.hpp>
#include <Kigen/utils/Utils.hpp>

namespace conversion {

    std::string to_string(sf::Keyboard::Key key);
    std::string to_string(sf::Mouse::Button button);
    std::string to_string(sf::Joystick::Axis axis);
    std::string to_string(sf::Event::EventType event_type);

    sf::Keyboard::Key    to_KeyboardKey (const std::string &string);
    sf::Mouse::Button    to_MouseButton (const std::string &string);
    sf::Joystick::Axis   to_JoystickAxis(const std::string &string);
    sf::Event::EventType to_EventType   (const std::string &string);
};


#endif //INCLUDED_CONVERSION_HPP
