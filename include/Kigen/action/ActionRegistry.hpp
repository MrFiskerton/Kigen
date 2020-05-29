//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_ACTIONCONTOL_HPP
#define INCLUDED_ACTIONCONTOL_HPP

#include <functional>
#include <unordered_map>
#include "Action.hpp"

namespace kigen {

template<typename ActionID>
class ActionRegistry {
public:
    void insert(const ActionID &id, Action action);

    Action& operator[] (const ActionID &id);

    void erase(const ActionID &id);

    bool test(const ActionID &id);

    bool contains(const ActionID &id);

private:
    std::unordered_map<ActionID, Action> m_actions;
};

template<typename ActionID>
void ActionRegistry<ActionID>::insert(const ActionID &id, Action action) {
    m_actions[id] = std::move(action);
}

template<typename ActionID>
bool ActionRegistry<ActionID>::test(const ActionID &id) {
    if (!contains(id)) {
        Logger::warn("ActionRegistry<ActionID>::test", "id doesn't contain");
        return false;
    }
    return m_actions.at(id).test();
}

template<typename ActionID>
void ActionRegistry<ActionID>::erase(const ActionID &id) { m_actions.erase(id); }

template<typename ActionID>
bool ActionRegistry<ActionID>::contains(const ActionID &id) {
    return m_actions.find(id) != m_actions.end();
}

template<typename ActionID>
Action &ActionRegistry<ActionID>::operator[](const ActionID &id) {
    return m_actions[id];
}

} //namespace kigen
#endif //INCLUDED_ACTIONCONTOL_HPP
