//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 09.06.2020.
//

#ifndef YOSAI_ENTITYFACTORY_HPP
#define YOSAI_ENTITYFACTORY_HPP

#include <unordered_map>
#include <string>
#include <functional>
#include "World.hpp"

namespace kigen {
    class EntityFactory {
    private:
        using EntityName = std::string;
    public:
        using Builder = std::function<Entity::Ptr()>;
        Entity::Ptr create(const EntityName& name);
        void register_entity(const EntityName& name, Builder builder);
    private:
        std::unordered_map<EntityName, Builder> m_factories;
    };
}

#endif //YOSAI_ENTITYFACTORY_HPP
