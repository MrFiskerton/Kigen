//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#ifndef INCLUDED_STATEMACHINE_HPP
#define INCLUDED_STATEMACHINE_HPP

#include <vector>
#include <functional>
#include <map>

#include <SFML/System/Time.hpp>

#include "State.hpp"
#include <Kigen/utils/NonCopyable.hpp>

namespace sf {
    class Event;
    class RenderTarget;
}

template <typename Identifier>
class StateControl : private NonCopyable {
public:
    enum StateAction : int {
        Push,
        Pop,
        Clear
    };
public:
    explicit StateControl();

    void update(const sf::Time& deltaTime);

    void draw(sf::RenderTarget &renderTarget);

    void handleEvent(const sf::Event &event);

    void pushState(Identifier id);

    void forcePushState(Identifier id);

    void popState();

    void clearStates();

    template<typename T>
    void registerState(Identifier id);

    bool isEmpty() const;

private:
    State::Ptr createState(Identifier id);

    void applyPendingChanges();

private:
    struct PendingChange {
        PendingChange(StateAction action, Identifier id) : m_action(action), m_stateId(id) {}
        StateAction m_action;
        Identifier m_stateId;
    };

private:
    std::vector <State::Ptr> m_stack;
    std::vector <PendingChange> m_pending_list;
    std::map <Identifier, std::function<State::Ptr()>> m_state_factories;
};

//------------------------------[   Definition for template function   ]------------------------------//
template<typename T, typename Identifier>
void StateControl::registerState(Identifier id) {
    m_state_factories[id] = [this]() {
        return State::Ptr(new T(*this));
    };
}

#endif //INCLUDED_STATEMACHINE_HPP
