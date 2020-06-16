//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#include "Kigen/world/component/Component.hpp"

namespace kigen{
    Component::Component(): m_owner_UID(0u) {}

    void Component::on_attach(Entity &entity) { }

    void Component::set_owner_UID(sf::Uint64 uid) { m_owner_UID = uid; }

    void Component::set_name(const std::string &name) { m_name = name; }

    sf::Uint64 Component::get_owner_UID() const { return m_owner_UID; }

    const std::string &Component::get_name() const { return m_name; }

    void Component::entity_update(Entity &entity, float dt) {}

    void Component::receive_message(const Message &message) { }
}

