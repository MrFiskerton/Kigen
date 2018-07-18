//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_ACTION_HPP
#define INCLUDED_ACTION_HPP


#include <SFML/Window/Event.hpp>

class InputControl;

class Action {
public:
    enum ActionType {
        Hold,
        Pressed,
        Released
    };
public:
    // Default constructor: Required for ActionMap::operator[] - constructs an uninitialized action
    Action();

    explicit Action(const sf::Keyboard::Key &key, ActionType type = Hold);

    explicit Action(const sf::Mouse::Button &button, ActionType type = Hold);

    explicit Action(sf::Event::EventType eventType);

    // Tests if the {event}/{real time input} constellation in the argument is true for this action
    bool test(InputControl& input) const;

public:
    bool operator==(const sf::Event &event) const;

    bool operator==(const Action &other) const;

    friend Action operator||(const Action &lhs, const Action &rhs);

    friend Action operator&&(const Action &lhs, const Action &rhs);

    friend Action operator!(const Action &action);
private:
    template<typename> friend
    class ActionControl;

private:
    ActionType m_type;
    ActionLogicalExpression  m_expression;
};

Action operator|| (const Action& lhs, const Action& rhs);
Action operator&& (const Action& lhs, const Action& rhs);
Action operator!(const Action &action);

#endif //INCLUDED_ACTION_HPP
