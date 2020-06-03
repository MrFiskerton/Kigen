//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#include "Kigen/world/Component.hpp"

namespace kigen{
    Component::Component() : m_parent_UID(0u) {}

    Component::~Component() { }

    void Component::on_start(Entity &entity) { }

    void Component::set_parent_UID(sf::Uint64 uid) { m_parent_UID = uid; }

    void Component::set_name(const std::string &name) { m_name = name; }

    sf::Uint64 Component::get_parent_UID() const { return m_parent_UID; }

    const std::string &Component::get_name() const { return m_name; }
}

