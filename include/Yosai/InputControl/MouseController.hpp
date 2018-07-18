//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_MOUSECONTROLLER_HPP
#define INCLUDED_MOUSECONTROLLER_HPP


#include <SFML/Window.hpp>
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

    void clear_event_buffer() override;
    void handle_event(const sf::Event &event) override;

    void set_window(sf::RenderWindow* window);

    bool isMouseOver(const sf::FloatRect& boundingBox, bool useDefaultView = false) const;
    bool isMouseWheelScrolledDown() const;
    bool isMouseWheelScrolledUp() const;
    void setMouseWheelScrollTicks(float deltaTicks);

    const sf::Vector2f& getMousePosition(bool useDefaultView = false) const;

private:
    bool test(sf::Mouse::Button button, MouseActionType action) const;
    bool test(sf::Mouse::Button button, MouseActionType action, const sf::FloatRect& boundingBox, bool useDefaultView = false) const;
private:
    //+ buffer

    float m_mouseWheelScrollTicks = 0;

    bool m_isMouseInsideView;
    sf::Vector2f m_mousePosition;
    sf::Vector2f m_defaultViewMousePosition;

    sf::RenderWindow* m_window;
};

#endif //INCLUDED_MOUSECONTROLLER_HPP
