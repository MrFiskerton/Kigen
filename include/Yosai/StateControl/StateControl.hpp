//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#ifndef INCLUDED_STATEMACHINE_HPP
#define INCLUDED_STATEMACHINE_HPP

#include <vector>
#include <functional>
#include <map>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include "State.hpp"
#include <Yosai/Util/Util.hpp>

namespace sf {
    class Event;
    class RenderTarget;
}

class StateControl : private sf::NonCopyable {
public:
    enum Action : int {
        Push,
        Pop,
        Clear
    };
public:
    explicit StateControl();

    void update(const sf::Time& deltaTime);

    void draw(sf::RenderTarget &renderTarget);

    void handleEvent(const sf::Event &event);

    void pushState(state::ID id);

    void forcePushState(state::ID id);

    void popState();

    void clearStates();

    template<typename T>
    void registerState(state::ID id);

    bool isEmpty() const;

private:
    State::Ptr createState(state::ID id);

    void applyPendingChanges();

private:
    struct PendingChange {
        explicit PendingChange(Action action, state::ID id = state::ID::None);

        Action action;
        state::ID id;
    };

private:
    std::vector <State::Ptr> m_stack;
    std::vector <PendingChange> m_pending_list;
    std::map <state::ID, std::function<State::Ptr()>> m_state_factories;
};

//------------------------------[   Definition for template function   ]------------------------------//
template<typename T>
void StateControl::registerState(state::ID id) {
    m_state_factories[id] = [this]() {
        return State::Ptr(new T(*this));
    };
}

#endif //INCLUDED_STATEMACHINE_HPP
