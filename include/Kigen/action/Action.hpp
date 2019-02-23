//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_ACTION_HPP
#define INCLUDED_ACTION_HPP


#include <SFML/Window/Event.hpp>
#include "./detail/ActionExpression.hpp"

namespace detail {
    class EventBuffer;
}

class Action {
public:
    enum ActionType : unsigned char {
        RealTime = 1u,
        Pressed  = 1u << 1,
        Released = 1u << 2
    };

public:
    // Default constructor: Required for ActionMap::operator[] - constructs an uninitialized action
    Action();
    explicit Action(const sf::Keyboard::Key &key, unsigned char type = RealTime | Pressed);
    explicit Action(const sf::Mouse::Button &button, unsigned char type = RealTime | Pressed);
    explicit Action(sf::Event::EventType event_type);

    // Tests if the {event}/{real time input} constellation in the argument is true for this action
    bool test(detail::EventBuffer& buffer) const;
private:
    // Construct an StateAction from expression(ActionNode)
    explicit Action(detail::ActionNode::Ptr expression);

public:
    //friend StateAction custom_action(std::function<bool(const sf::Event&)> trigger);
    friend Action custom_action(std::function<bool()> trigger);
public:
    // bool operator==(const sf::Event &event) const;
    // bool operator==(const StateAction &other) const;
    friend Action operator||(const Action &lhs, const Action &rhs);
    friend Action operator&&(const Action &lhs, const Action &rhs);
    friend Action operator!(const Action &action);
private:
    std::shared_ptr<detail::ActionNode> m_expression;
};

//StateAction custom_action(std::function<bool(const sf::Event&)> trigger);
Action custom_action(std::function<bool()> trigger);

Action operator|| (const Action& lhs, const Action& rhs);
Action operator&& (const Action& lhs, const Action& rhs);
Action operator!(const Action &action);

#endif //INCLUDED_ACTION_HPP
