//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_ABSTRACTDEVICECONTROLLER_HPP
#define INCLUDED_ABSTRACTDEVICECONTROLLER_HPP


#include <Kigen/graphics/Window.hpp>
#include <Kigen/utils/Logger.hpp>
#include <Kigen/conversion/to_string.hpp>
#include "KeyActionType.hpp"
#include <SFML/Window/Event.hpp>
#include <Kigen/utils/locator/IService.hpp>

namespace kigen {
namespace device {

class AbstractDevice: public IService {
public:
    AbstractDevice() : m_enabled(true) {}

    virtual ~AbstractDevice() = default;

    virtual void clear() = 0;

    virtual void push(const sf::Event &event) = 0;

    void disable() { m_enabled = false; }

    void enable() { m_enabled = true; }

    bool is_enabled() const { return m_enabled; }

private:
    bool m_enabled;
};

class NullDevice : public AbstractDevice {
public:
    void clear() override {}

    void push(const sf::Event &event) override {}
};

} //namespace device
} //namespace kigen

#endif //INCLUDED_ABSTRACTDEVICECONTROLLER_HPP
