//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_ACTIONCONTOL_HPP
#define INCLUDED_ACTIONCONTOL_HPP

#include <functional>
#include <unordered_map>

namespace kigen {

template<typename ActionID>
class CallbackMap {
    friend class ActionControl;
public:
    typedef std::function<void()> callback_t;
public:
    void connect(const ActionID &id, callback_t callback);

    void disconnect(const ActionID &id);

    void trigger(const ActionID &id);

    bool contains(const ActionID &id);

private:
    std::unordered_map<ActionID, callback_t> m_callbacks;
};

template<typename ActionID>
void CallbackMap<ActionID>::connect(const ActionID &id, CallbackMap::callback_t callback) {
    m_callbacks.at(id) = std::move(callback);
}

template<typename ActionID>
void CallbackMap<ActionID>::trigger(const ActionID &id) {
    if (!contains(id)) return;
    m_callbacks.at(id)();
}

template<typename ActionID>
void CallbackMap<ActionID>::disconnect(const ActionID &id) { m_callbacks.erase(id); }

template<typename ActionID>
bool CallbackMap<ActionID>::contains(const ActionID &id) {
    return m_callbacks.find(id) != m_callbacks.end();
}

} //namespace kigen
#endif //INCLUDED_ACTIONCONTOL_HPP
