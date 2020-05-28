//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.03.19.
//

#ifndef YOSAI_REALTIMENODE_HPP
#define YOSAI_REALTIMENODE_HPP

#include <functional>

namespace kigen {
namespace action {

class RealtimeActionNode : public ActionNode {
public:
    bool test(const InputControl &buffer) const override { return isRealtimeActive(); }

    bool test() const override { return isRealtimeActive(); }

    virtual bool isRealtimeActive() const = 0;
};

// Operation node class for keys currently held down
class KeyboardRealtimeLeaf : public RealtimeActionNode {
public:
    explicit KeyboardRealtimeLeaf(sf::Keyboard::Key key, bool pressed) : m_key(key), m_pressed(pressed) {}

    bool isRealtimeActive() const override {
        return sf::Keyboard::isKeyPressed(m_key) == m_pressed;
    }

private:
    sf::Keyboard::Key m_key{};
    bool m_pressed;
};

// Operation node class for mouse buttons currently held down
class MouseRealtimeLeaf : public RealtimeActionNode {
public:
    explicit MouseRealtimeLeaf(sf::Mouse::Button button, bool pressed) : m_button(button), m_pressed(pressed) {}

    bool isRealtimeActive() const override {
        return sf::Mouse::isButtonPressed(m_button) == m_pressed;
    }

private:
    sf::Mouse::Button m_button{};
    bool m_pressed;
};

// Operation node class for user-defined realtime-based actions
class CustomRealtimeLeaf : public RealtimeActionNode {
public:
    explicit CustomRealtimeLeaf(std::function<bool()> trigger) : m_trigger(std::move(trigger)) {}

    bool isRealtimeActive() const override { return m_trigger(); }

private:
    std::function<bool()> m_trigger;
};

} //namespace action
} //namespace kigen

#endif //YOSAI_REALTIMENODE_HPP 
