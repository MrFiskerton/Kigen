//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_COMPONENT_HPP
#define YOSAI_COMPONENT_HPP

#include <Kigen/utils/locator/Locator.hpp>
#include <Kigen/utils/NonCopyable.hpp>
#include <Kigen/utils/Destructible.hpp>
#include <Kigen/world/message/Communicable.hpp>
#include <SFML/Config.hpp>
#include <memory>


namespace kigen {
    class Entity;

    class Component : private NonCopyable, public Destructible, public Communicable {
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
        virtual void on_attach(Entity &entity);
        void set_owner_UID(sf::Uint64 uid);
        void set_name(const std::string &name);
        sf::Uint64 get_owner_UID() const;
        const std::string &get_name() const;

        void receive_message(const Message &message) override;

    private:
        sf::Uint64 m_owner_UID;
        std::string m_name;
    };
}

#endif //YOSAI_COMPONENT_HPP
