//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.03.19.
//

#ifndef YOSAI_ACTIONLEAVES_HPP
#define YOSAI_ACTIONLEAVES_HPP

#include "ActionNode.hpp"
#include <Kigen/utils/locator/Locator.hpp>


namespace kigen {
namespace action {

class KeyboardLeaf : public ActionNode {
public:
    KeyboardLeaf(sf::Keyboard::Key key, unsigned char type): m_key(key), m_type(type) {}

    bool test() const override {
        return Locator::locate<InputControl>().keyboard().test(m_key, m_type);
    }

private:
    sf::Keyboard::Key m_key;
    unsigned char m_type;
};


// Operation node class for user-defined realtime-based actions
class CustomRealtimeLeaf : public ActionNode {
public:
    explicit CustomRealtimeLeaf(std::function<bool()> trigger) : m_trigger(std::move(trigger)) {}

    bool test() const override { return m_trigger(); }

private:
    std::function<bool()> m_trigger;
};

} //namespace action
} //namespace kigen

#endif //YOSAI_ACTIONLEAVES_HPP
