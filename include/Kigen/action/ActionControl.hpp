//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_ACTIONMAP_HPP
#define INCLUDED_ACTIONMAP_HPP

#include <map>
#include "Action.hpp"
#include "ActionRegistry.hpp"

namespace kigen {

template<typename ActionID>
class ActionControl : private NonCopyable {
public:
    typedef std::function<void()> callback_t;
public:
    void connect(const ActionID &id, callback_t callback);

    bool is_activated(const ActionID &id);

    void invoke_callbacks();

    ActionRegistry<ActionID>& get_registry();
private:
    ActionRegistry<ActionID> m_registry;
    std::unordered_map<ActionID, callback_t> m_callbacks;
};

template<typename ActionID>
bool ActionControl<ActionID>::is_activated(const ActionID &id) {
    return m_registry.test(id);
}

template<typename ActionID>
void ActionControl<ActionID>::invoke_callbacks() {
    std::for_each(m_callbacks.begin(), m_callbacks.end(), [&](auto &element) {
        if (is_activated(element.first)) element.second(); // trigger
    });
}

template<typename ActionID>
void ActionControl<ActionID>::connect(const ActionID &id, ActionControl::callback_t callback) {
    if (!m_registry.contains(id)) {
        Logger::warn("ActionControl<ActionID>::connect", "id doesn't contain in registry");
        return;
    }
    m_callbacks[id] = std::move(callback);
}

template<typename ActionID>
ActionRegistry<ActionID> &ActionControl<ActionID>::get_registry() {
    return m_registry;
}

} //namespace kigen

#endif //INCLUDED_ACTIONMAP_HPP
