//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_MOUSECONTROLLER_HPP
#define INCLUDED_MOUSECONTROLLER_HPP


#include <SFML/Window.hpp>
#include <map>
#include "AbstractDeviceController.hpp"

class MouseController: public AbstractDeviceController {
public:
    enum MouseActionType {
        Hold,
        Pressed,
        Clicked // Released
    };
public:
    MouseController();
    virtual ~MouseController();

    void clear_events() override;
    void handle_event(const sf::Event &event) override;

    void set_window(sf::RenderWindow* window);

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

    bool isMouseOver(const sf::FloatRect& boundingBox, bool useDefaultView = false) const;
    bool isMouseWheelScrolledDown() const;
    bool isMouseWheelScrolledUp() const;

    const sf::Vector2f& getMousePosition(bool useDefaultView = false) const;

private:
    bool test(sf::Mouse::Button button, MouseActionType action) const;
    bool test(sf::Mouse::Button button, MouseActionType action, const sf::FloatRect& boundingBox, bool useDefaultView = false) const;
private:
    std::multimap<sf::Mouse::Button, MouseActionType> m_event_buffer;

    bool m_isMouseInsideView;
    bool m_isMouseMoved;

    sf::Vector2f m_mousePosition;
    sf::Vector2f m_defaultViewMousePosition;

    float m_mouseWheelScrollTicks = 0;

    sf::RenderWindow* m_window;
};

//------------------------------[   Definition for template function   ]------------------------------//
template<typename ... Args>
bool MouseController::isButtonPressed(sf::Mouse::Button button, Args &&... args) {
    return test(button, Hold, args...);
}

template<typename... Args>
bool MouseController::isButtonReleased(sf::Mouse::Button button, Args &&... args) {
    return !isButtonPressed(button, std::forward<Args>(args)...);
}

template<typename ... Args>
bool MouseController::isButtonJustPressed(sf::Mouse::Button button, Args &&... args) {
    return test(button, Pressed, std::forward<Args>(args)...);
}

template<typename ... Args>
bool MouseController::isButtonJustReleased(sf::Mouse::Button button, Args &&... args) {
    return test(button, Clicked, std::forward<Args>(args)...);
}

#endif //INCLUDED_MOUSECONTROLLER_HPP
