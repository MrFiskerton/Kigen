//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#include <Kigen/action/Action.hpp>

namespace kigen {

Action::Action(sf::Keyboard::Key key, unsigned char type)
         : m_expression(std::make_shared<action::KeyboardLeaf>(key, type)) {}

//Action::Action(sf::Mouse::Button button, unsigned char type) {   //}

//Action::Action(sf::Event::EventType eventType) : m_expression(std::make_shared<action::MiscEventLeaf>(eventType)) {}

Action::Action(std::function<bool()> trigger)
        : m_expression(std::make_shared<action::CustomRealtimeLeaf>(std::move(trigger))) {}

bool Action::test() const {
    return m_expression->test();
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