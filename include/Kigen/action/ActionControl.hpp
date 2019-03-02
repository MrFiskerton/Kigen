//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_ACTIONMAP_HPP
#define INCLUDED_ACTIONMAP_HPP

#include <map>
#include "Action.hpp"
#include "CallbackMap.hpp"

namespace kigen {

template<typename ActionID>
class ActionControl : private NonCopyable {
private:
    typedef std::unordered_map<ActionID, Action> Map;
    typedef CallbackMap<ActionID> CallbackMap;
public:
    ActionControl(ActionControl &&source) noexcept;

    ActionControl &operator=(ActionControl &&source) noexcept;

    Action &at(const ActionID &id);

    bool contains(const ActionID &id);

    bool remove(const ActionID &id);

    void clear();

    void update(sf::Window &window);

    bool is_active(const ActionID &id);

    void invoke_callbacks(CallbackMap &callback_map);

    EventBuffer &get_buffer();

private:
    EventBuffer m_buffer;
    Map m_actions;
};

template<typename ActionID>
void ActionControl<ActionID>::update(sf::Window &window) {
    m_buffer.update(window);
}

template<typename ActionID>
bool ActionControl<ActionID>::is_active(const ActionID &id) {
    if (!contains(id)) return false;
    return at(id).test(m_buffer);
}

template<typename ActionID>
void ActionControl<ActionID>::invoke_callbacks(CallbackMap &callback_map) {
    for (auto &element: callback_map.m_callbacks) {
        auto id = element.first;
        auto callback = element.second;
        if (is_active(id)) callback();
    }

//    std::for_each(callback_map.begin(), callback_map.end(),
//                  [](auto &element) { if (is_active(element.first)) element.second(); }
//    );
}

template<typename ActionID>
EventBuffer &ActionControl<ActionID>::get_buffer() {
    return m_buffer;
}

template<typename ActionID>
bool ActionControl<ActionID>::contains(const ActionID &id) {
    return m_actions.find(id) != m_actions.end();
}

template<typename ActionID>
ActionControl<ActionID>::ActionControl(ActionControl &&source) noexcept {

}

template<typename ActionID>
ActionControl &ActionControl<ActionID>::operator=(ActionControl &&source) noexcept {
    return <#initializer#>;
}

template<typename ActionID>
Action &ActionControl<ActionID>::at(const ActionID &id) {
    return <#initializer#>;
}

template<typename ActionID>
bool ActionControl<ActionID>::remove(const ActionID &id) {
    return false;
}

template<typename ActionID>
void ActionControl<ActionID>::clear() {

}

} //namespace kigen

#endif //INCLUDED_ACTIONMAP_HPP
