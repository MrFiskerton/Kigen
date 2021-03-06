//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_ACTION_HPP
#define INCLUDED_ACTION_HPP

#include <Kigen/input/KeyActionType.hpp>
#include <Kigen/action/detail/ActionNode.hpp>
#include <Kigen/action/detail/ActionLeaves.hpp>
#include <Kigen/action/detail/LogicNode.hpp>

namespace kigen {

class InputControl;

class Action {
public:
    // Default constructor: Required for ActionControl::operator[] - constructs an uninitialized action
    Action() = default;

    explicit Action(sf::Keyboard::Key key, unsigned char type = RealTime | Pressed);

    //explicit Action(sf::Mouse::Button button, unsigned char type = RealTime | Pressed);

    //explicit Action(sf::Event::EventType event_type);

    explicit Action(std::function<bool()> trigger);

    bool test() const;

private:
    // Construct an Action from expression(ActionNode)
    explicit Action(action::ActionNode::Ptr expression);

public:
    friend Action operator||(const Action &lhs, const Action &rhs);

    friend Action operator&&(const Action &lhs, const Action &rhs);

    friend Action operator!(const Action &action);

private:
    std::shared_ptr<action::ActionNode> m_expression;
};

Action operator||(const Action &lhs, const Action &rhs);

Action operator&&(const Action &lhs, const Action &rhs);

Action operator!(const Action &action);

} //namespace kigen

#endif //INCLUDED_ACTION_HPP
