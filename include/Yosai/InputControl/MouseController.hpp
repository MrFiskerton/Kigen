//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_MOUSECONTROLLER_HPP
#define INCLUDED_MOUSECONTROLLER_HPP


#include <SFML/Window.hpp>
#include "AbstractDeviceController.hpp"

class MouseController: public AbstractDeviceController {
public:
    enum ActionType {
        RealtimePressed,
        Pressed,
        Clicked // Released
    };
public:
    MouseController();
    virtual ~MouseController();

    void update() override;
    void handle_event(const sf::Event &event) override;
    bool test(sf::Mouse::Button button, ActionType action) const;
    bool test(sf::Mouse::Button button, ActionType action, const sf::FloatRect& boundingBox, bool useDefaultView = false) const;

    void set_window(sf::RenderWindow* window);

    bool isMouseOver(const sf::FloatRect& boundingBox, bool useDefaultView = false) const;
    bool isMouseWheelScrolledDown() const;
    bool isMouseWheelScrolledUp() const;

    const sf::Vector2f& getMousePosition(bool useDefaultView = false) const;

    void setMouseWheelScrollTicks(float deltaTicks);

private:
    //+ buffer

    float m_mouseWheelScrollTicks = 0;

    bool m_isMouseInsideView;
    sf::Vector2f m_mousePosition;
    sf::Vector2f m_defaultViewMousePosition;

    sf::RenderWindow* m_window;
};

#endif //INCLUDED_MOUSECONTROLLER_HPP
