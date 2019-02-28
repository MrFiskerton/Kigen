//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_ABSTRACTDEVICECONTROLLER_HPP
#define INCLUDED_ABSTRACTDEVICECONTROLLER_HPP


#include <SFML/Graphics/RenderWindow.hpp>
#include <Kigen/utils/Logger.hpp>
#include <Kigen/conversion/to_string.hpp>

class AbstractDevice {
public:
    AbstractDevice();

    virtual ~AbstractDevice() = default;

    virtual void clear_events() = 0;

    virtual void handle_event(const sf::Event &event) = 0;

    virtual void lock();

    virtual void unlock();

    virtual bool is_locked() const;

private:
    bool is_action_locked;
};


#endif //INCLUDED_ABSTRACTDEVICECONTROLLER_HPP
