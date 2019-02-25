//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#include <Kigen/action/Action.hpp>

Action::Action(): m_expression() {}

Action::Action(const sf::Keyboard::Key &key, unsigned char type) {
    if(type & RealTime) {
        m_expression = std::make_shared<detail::KeyboardRealtimeLeaf>(key, type & Pressed);
    } else {
        m_expression = std::make_shared<detail::KeyboardEventLeaf>(key, type & Pressed);
    }
}

Action::Action(const sf::Mouse::Button &button, unsigned char type) {
    if(type & RealTime) {
        m_expression = std::make_shared<detail::MouseRealtimeLeaf>(button, type & Pressed);
    } else {
        m_expression = std::make_shared<detail::MouseEventLeaf>(button, type & Pressed);
    }
}

Action::Action(sf::Event::EventType eventType): m_expression(std::make_shared<detail::MiscEventLeaf>(eventType)) {}

bool Action::test(detail::EventBuffer &buffer) const {
    return m_expression->test(buffer);
}

Action::Action(detail::ActionNode::Ptr expression) {
    m_expression = std::move(expression);
}

/*Action custom_action(std::function<bool(const sf::Event &)> trigger) {
    return Action(std::make_shared<detail::CustomEventLeaf>(std::move(trigger)));
}*/

Action custom_action(std::function<bool()> trigger) {
    return Action(std::make_shared<detail::CustomRealtimeLeaf>(std::move(trigger)));
}

Action operator||(const Action &lhs, const Action &rhs) {
    return Action(std::make_shared<detail::OrNode>(lhs.m_expression, rhs.m_expression));
}

Action operator&&(const Action &lhs, const Action &rhs) {
    return Action(std::make_shared<detail::AndNode>(lhs.m_expression, rhs.m_expression));
}

Action operator!(const Action &action) {
    return Action(std::make_shared<detail::NotNode>(action.m_expression));
}
