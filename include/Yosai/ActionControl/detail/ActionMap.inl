//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

template<typename ActionId>
ActionMap<ActionId>::ActionMap(ActionMap &&source) noexcept: m_actions(std::move(source.m_actions)),
                                                             m_buffer(std::move(source.m_buffer)) {}

template<typename ActionId>
ActionMap<ActionId> &ActionMap<ActionId>::operator=(ActionMap &&source) noexcept {
    m_actions = std::move(source.m_actions);
    m_buffer = std::move(source.m_buffer);
    return *this;
}

template<typename ActionId>
bool ActionMap<ActionId>::contains(const ActionId &id) {
    return m_actions.find(id) == m_actions.end();
}

template<typename ActionId>
Action &ActionMap<ActionId>::at(const ActionId &id) {
    return m_actions.at(id);
}

template<typename ActionId>
bool ActionMap<ActionId>::remove(const ActionId &id) {
    if (!contains(id)) return false;
    m_actions.erase(id);
    return true;
}

template<typename ActionId>
void ActionMap<ActionId>::clear() {
    m_actions.clear();
}

template<typename ActionId>
Action &ActionMap<ActionId>::operator[](const ActionId &id) {
    return m_actions[id];
}

template<typename ActionId>
bool ActionMap<ActionId>::test(const ActionId &id) {
    return m_actions[id].test(m_buffer);
}

template<typename ActionId>
void ActionMap<ActionId>::handle_event(const sf::Event &event) {
    m_buffer.push(event);
}

template<typename ActionId>
void ActionMap<ActionId>::clear_events() {
    m_buffer.clear();
}

template<typename ActionId>
void ActionMap<ActionId>::invoke_callbacks(ActionControl& control) {
    for(auto& action_pair: m_actions) {
        if (!action_pair.second.test(m_buffer)) continue;
        control.trigger(action_pair.first);
    }
}
