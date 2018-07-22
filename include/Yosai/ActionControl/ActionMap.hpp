//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 17.07.18.
//

#ifndef INCLUDED_ACTIONMAP_HPP
#define INCLUDED_ACTIONMAP_HPP

#include <map>
#include <Yosai/Util/NonCopyable.hpp>
#include "Action.hpp"

template<typename ActionId>
class ActionMap : private NonCopyable {
private:
    typedef std::map <ActionId, Action> Map;
public:
    ActionMap();
    ActionMap(ActionMap &&source);
    ActionMap &operator=(ActionMap &&source);

    void remove(const ActionId &id);
    void clear();
    bool test(const ActionId &id) const;

    void invoke_callbacks();
public:
    Action &operator[](const ActionId &id);
private:
    Map m_action_map;
};

// Realisation
#include "./detail/ActionMap.inl"

#endif //INCLUDED_ACTIONMAP_HPP
