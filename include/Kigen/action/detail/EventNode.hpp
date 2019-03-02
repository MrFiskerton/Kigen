//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.03.19.
//

#ifndef YOSAI_EVENTNODE_HPP
#define YOSAI_EVENTNODE_HPP

#include "ActionNode.hpp"
#include <Kigen/input/EventBuffer.hpp>

namespace kigen {
namespace action {

// Class between ActionNode and concrete Event classes
class EventNode : public ActionNode {
public:
    bool test(const EventBuffer &buffer) const override {
        return buffer.contains(*this);
    }

    virtual bool isEventActive(const sf::Event &event) const = 0;

protected:
    sf::Event m_event{};
};

// Operation node class for key events (either pressed or released)
class KeyboardEventLeaf : public EventNode {
public:
    KeyboardEventLeaf(sf::Keyboard::Key key, bool pressed) {
        m_event.type = pressed ? sf::Event::KeyPressed : sf::Event::KeyReleased;
        m_event.key.code = key;
    }

    bool isEventActive(const sf::Event &event) const override {
        return event.type == m_event.type && event.key.code == m_event.key.code;
    }
};

// Operation node class for mouse button events (either pressed or released)
class MouseEventLeaf : public EventNode {
public:
    MouseEventLeaf(sf::Mouse::Button button, bool pressed) {
        m_event.type = pressed ? sf::Event::MouseButtonPressed : sf::Event::MouseButtonReleased;
        m_event.mouseButton.button = button;
    }

    bool isEventActive(const sf::Event &event) const override {
        return event.type == m_event.type && event.mouseButton.button == m_event.mouseButton.button;
    }
};

// Operation node class for other SFML events
class MiscEventLeaf : public EventNode {
public:
    explicit MiscEventLeaf(sf::Event::EventType event_type) {
        m_event.type = event_type;
    }

    bool isEventActive(const sf::Event &event) const override {
        return m_event.type == event.type;
    };
};

// Operation node class for user-defined event-based actions
class CustomEventLeaf : public EventNode {
public:
    explicit CustomEventLeaf(std::function<bool(const sf::Event &)> trigger) : m_trigger(std::move(trigger)) {}

    bool isEventActive(const sf::Event &event) const override {
        return m_trigger(event);
    }

private:
    std::function<bool(const sf::Event &)> m_trigger{};
};

} //namespace action
} //namespace kigen

#endif //YOSAI_EVENTNODE_HPP 
