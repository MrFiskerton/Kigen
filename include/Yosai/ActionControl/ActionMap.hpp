//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_ACTIONMAP_HPP
#define INCLUDED_ACTIONMAP_HPP

#include <map>
#include <Yosai/Util/NonCopyable.hpp>
#include "Action.hpp"
#include "ActionControl.hpp"

template<typename ActionId>
class ActionMap : private NonCopyable {
private:
    typedef std::map <ActionId, Action> Map;
    typedef ActionContol<ActionId> ActionControl;
public:
    ActionMap() = default;
    ActionMap(ActionMap &&source) noexcept;
    ActionMap &operator=(ActionMap &&source) noexcept;

    Action& at(const ActionId &id);
    bool contains(const ActionId &id);
    bool remove(const ActionId &id);
    bool is_active(const ActionId &id);
    void clear();

    void handle_event(const sf::Event& event);
    void clear_events();

    void invoke_callbacks(ActionControl& control);
public:
    Action &operator[](const ActionId &id);
private:
    Map m_actions;
    detail::EventBuffer m_buffer;
};

// Realisation
#include "./detail/ActionMap.inl"

#endif //INCLUDED_ACTIONMAP_HPP
