//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_INPUTCONTROL_HPP
#define INCLUDED_INPUTCONTROL_HPP

#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Window.hpp"

namespace kigen {

class EventBuffer final : public device::Window, public device::Keyboard, public device::Mouse {
public:
    enum Device {
        Unknown,
        Window,
        Keyboard,
        Mouse,
        Joystick,
        All
    };

public:
    void lock_device(Device device = All);

    void unlock_device(Device device = All);

    bool is_locked(Device device = All) const;

    void update(sf::Window &window);

    void clear_events() override;

    void handle_event(const sf::Event &event) override;

private:
    Device get_compatible_device(const sf::Event &event);

    void poll_events(sf::Window &window);
};

} // namespace kigen

#endif //INCLUDED_INPUTCONTROL_HPP
