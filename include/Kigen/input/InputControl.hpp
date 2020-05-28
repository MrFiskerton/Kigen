//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_INPUTCONTROL_HPP
#define INCLUDED_INPUTCONTROL_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "WindowStatus.hpp"

namespace kigen {
namespace action {
    class EventNode;
}

class InputControl : public device::AbstractDevice {
public:
    device::WindowStatus &window();

    device::Keyboard &keyboard();

    device::Mouse &mouse();

    void update(sf::Window &window);

    void clear() override;

    void push(const sf::Event &event) override;

private:
    device::AbstractDevice &get_compatible_device(const sf::Event &event);

    void poll_events(sf::Window &window);

private:
    device::WindowStatus m_window;
    device::Keyboard m_keyboard;
    device::Mouse m_mouse;
    device::NullDevice m_null;

    std::vector<sf::Event> m_buffer;
};

} // namespace kigen

#endif //INCLUDED_INPUTCONTROL_HPP
