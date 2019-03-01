//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_MOUSECONTROLLER_HPP
#define INCLUDED_MOUSECONTROLLER_HPP

#include <map>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "DeviceBuffer.hpp"

namespace kigen {
namespace device {

class Mouse : public DeviceBuffer {
public:
    enum MouseActionType {
        Hold,
        Pressed,
        Clicked // Pressed and Released
    };
public:
    void clear_events() override;

    void handle_event(const sf::Event &event) override;

    void update_position(const sf::Window& window);

    template<typename ... Args>
    bool isButtonPressed(sf::Mouse::Button button, Args &&... args);

    template<typename ... Args>
    bool isButtonReleased(sf::Mouse::Button button, Args &&... args);

    template<typename ... Args>
    bool isButtonJustPressed(sf::Mouse::Button button, Args &&... args);

    template<typename ... Args>
    bool isButtonJustReleased(sf::Mouse::Button button, Args &&... args);

    bool isMouseInsedeView();

    bool isMouseMoved();

    bool isMouseOver(const sf::FloatRect &boundingBox, bool useDefaultView = false) const;

    bool isMouseWheelScrolledDown() const;

    bool isMouseWheelScrolledUp() const;

    const sf::Vector2f &getMousePosition(bool useDefaultView = false) const;

private:
    bool test(sf::Mouse::Button button, MouseActionType action) const;

    bool test(sf::Mouse::Button button, MouseActionType action, const sf::FloatRect &boundingBox,
              bool useDefaultView = false) const;

private:
    std::multimap<sf::Mouse::Button, MouseActionType> m_event_buffer;

    bool m_isMouseInsideView;
    bool m_isMouseMoved;

    sf::Vector2f m_mousePosition;
    sf::Vector2f m_defaultViewMousePosition;

    float m_mouseWheelScrollTicks = 0;
};

//------------------------------[   Definition for template function   ]------------------------------//
template<typename ... Args>
bool Mouse::isButtonPressed(sf::Mouse::Button button, Args &&... args) {
    return test(button, Hold, args...);
}

template<typename... Args>
bool Mouse::isButtonReleased(sf::Mouse::Button button, Args &&... args) {
    return !isButtonPressed(button, std::forward<Args>(args)...);
}

template<typename ... Args>
bool Mouse::isButtonJustPressed(sf::Mouse::Button button, Args &&... args) {
    return test(button, Pressed, std::forward<Args>(args)...);
}

template<typename ... Args>
bool Mouse::isButtonJustReleased(sf::Mouse::Button button, Args &&... args) {
    return test(button, Clicked, std::forward<Args>(args)...);
}

} //namespace device
} //namespace kigen
#endif //INCLUDED_MOUSECONTROLLER_HPP
