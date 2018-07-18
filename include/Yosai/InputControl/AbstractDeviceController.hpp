//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_ABSTRACTDEVICECONTROLLER_HPP
#define INCLUDED_ABSTRACTDEVICECONTROLLER_HPP


#include <SFML/Graphics/RenderWindow.hpp>
#include <Yosai/Util/Logger.hpp>

class AbstractDeviceController {
public:
    AbstractDeviceController();
    virtual ~AbstractDeviceController() = default;

    virtual void update() = 0;
    virtual void handle_event(const sf::Event &event) = 0;

    void lock_action();
    void unlock_action();
    bool is_locked() const;

private:
    bool is_action_locked;
};


#endif //INCLUDED_ABSTRACTDEVICECONTROLLER_HPP
