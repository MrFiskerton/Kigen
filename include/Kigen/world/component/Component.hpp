//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_COMPONENT_HPP
#define YOSAI_COMPONENT_HPP

#include <Kigen/utils/NonCopyable.hpp>
#include "Kigen/utils/Destructible.hpp"
#include <SFML/Config.hpp>
#include <memory>


namespace kigen {
    class Entity;

    class Component : private NonCopyable, public Destructible {
    public:
        using Ptr = std::unique_ptr<Component>;
        enum class Type {
            Drawable,
            Physics,
            Script
        };
    public:
        explicit Component();
        virtual Type type() const = 0;
        virtual void entity_update(Entity &entity, float dt);
        virtual void on_start(Entity &entity);
        void set_owner_UID(sf::Uint64 uid);
        void set_name(const std::string &name);
        sf::Uint64 get_parent_UID() const;
        const std::string &get_name() const;
    private:
        sf::Uint64 m_owner_UID;
        std::string m_name;
    };
}

#endif //YOSAI_COMPONENT_HPP
