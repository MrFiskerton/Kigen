//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_ABSTRACTDEVICECONTROLLER_HPP
#define INCLUDED_ABSTRACTDEVICECONTROLLER_HPP


#include <Kigen/graphics/Window.hpp>
#include <Kigen/utils/Logger.hpp>
#include <Kigen/conversion/to_string.hpp>

namespace kigen {
namespace device {

enum KeyActionType : unsigned char {
    RealTime = 1u,
    Pressed = 1u << 1,
    Released = 1u << 2
};

class DeviceBuffer {
public:
    DeviceBuffer() : m_enabled(true) {}

    virtual ~DeviceBuffer() = default;

    virtual void clear_events() = 0;

    virtual void handle_event(const sf::Event &event) = 0;

    void disable() { m_enabled = false; }

    void enable() { m_enabled = true; }

    bool is_disabled() const { return !is_enabled(); }

    bool is_enabled() const { return m_enabled; }

private:
    bool m_enabled;
};

} //namespace device
} //namespace kigen

#endif //INCLUDED_ABSTRACTDEVICECONTROLLER_HPP
