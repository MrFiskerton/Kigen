//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#include <Kigen/action/Action.hpp>

namespace kigen {

Action::Action(const sf::Keyboard::Key &key, unsigned char type) {
    if (type & RealTime) {
        m_expression = std::make_shared<action::KeyboardRealtimeLeaf>(key, bool(type & Pressed));
    } else {
        m_expression = std::make_shared<action::KeyboardEventLeaf>(key, bool(type & Pressed));
    }
}

Action::Action(const sf::Mouse::Button &button, unsigned char type) {
    if (type & RealTime) {
        m_expression = std::make_shared<action::MouseRealtimeLeaf>(button, bool(type & Pressed));
    } else {
        m_expression = std::make_shared<action::MouseEventLeaf>(button, bool(type & Pressed));
    }
}

Action::Action(sf::Event::EventType eventType) : m_expression(std::make_shared<action::MiscEventLeaf>(eventType)) {}

Action::Action(std::function<bool()> &trigger)
        : m_expression(std::make_shared<action::CustomRealtimeLeaf>(std::move(trigger))) {}

Action::Action(std::function<bool(const sf::Event &)> &trigger)
        : m_expression(std::make_shared<action::CustomEventLeaf>(std::move(trigger))) {}

bool Action::test(EventBuffer &buffer) const {
    return m_expression->test(buffer);
}

Action::Action(action::ActionNode::Ptr expression) {
    m_expression = std::move(expression);
}

Action operator||(const Action &lhs, const Action &rhs) {
    return Action(std::make_shared<action::OrNode>(lhs.m_expression, rhs.m_expression));
}

Action operator&&(const Action &lhs, const Action &rhs) {
    return Action(std::make_shared<action::AndNode>(lhs.m_expression, rhs.m_expression));
}

Action operator!(const Action &action) {
    return Action(std::make_shared<action::NotNode>(action.m_expression));
}

} //namespace kigen