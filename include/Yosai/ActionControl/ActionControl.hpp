//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_ACTIONCONTOL_HPP
#define INCLUDED_ACTIONCONTOL_HPP

#include <functional>
#include <unordered_map>

template<typename ActionId>
class ActionContol {
public:
    typedef std::function<void()> Callback;
public:
    void connect(const ActionId& id, Callback callback);
    void disconnect(const ActionId& id);
    void trigger(const ActionId& id);
private:
    std::unordered_map<ActionId, Callback> m_callbacks;
};

template<typename ActionId>
void ActionContol<ActionId>::connect(const ActionId &id, ActionContol::Callback callback) {
    m_callbacks[id] = std::move(callback);
}

template<typename ActionId>
void ActionContol<ActionId>::trigger(const ActionId &id) {
    if (m_callbacks.find(id) == m_callbacks.end()) return;
    m_callbacks.at(id)();
}

template<typename ActionId>
void ActionContol<ActionId>::disconnect(const ActionId &id) {
    m_callbacks.erase(id);
}

// Realisation
#include "./detail/ActionControl.inl"

#endif //INCLUDED_ACTIONCONTOL_HPP
