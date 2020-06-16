//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 09.06.2020.
//

#include "Kigen/world/EntityFactory.hpp"

#include <utility>

namespace kigen {
    void EntityFactory::register_entity(const EntityName &name, Builder builder) {
        m_factories[name] = std::move(builder);
    }

    Entity::Ptr EntityFactory::create(const EntityName &name) {
        auto found = m_factories.find(name);
        assertion(found != m_factories.end(), "Entity not found in Entity factory");
        return found->second();
    }
}