//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_INPUTCONTROL_HPP
#define INCLUDED_INPUTCONTROL_HPP


#include "KeyboardController.hpp"
#include "EventBuffer.hpp"

class InputControl final: public KeyboardController {
public:
    enum Device {
        Non,
        Keyboard,
        Mouse,
        All,
        Count
    };



public:
    void lock_action(Device device = All);
    void unlock_action(Device device = All);
    bool is_locked(Device device = All) const;

    void clear_event_buffer() override;
    void handle_event(const sf::Event &event) override;
    void poll_events(sf::Window &window);
private:
    EventBuffer m_buffer;
};


#endif //INCLUDED_INPUTCONTROL_HPP
