//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_ENTITY_HPP
#define YOSAI_ENTITY_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <Kigen/utils/Utils.hpp>

#include <memory>
#include <vector>

#include "Kigen/world/component/Component.hpp"

namespace kigen {
    class World;

    class Entity final : public sf::Transformable, public sf::Drawable, private NonCopyable, public Destructible {
    public:
        using Ptr = std::unique_ptr<Entity>;

        explicit Entity();
        void update(float dt);
        void add_child(Ptr &child);

        template <typename T>
        void add_component(std::unique_ptr<T> &component);

        Ptr remove_child(Entity &child);
        sf::Vector2f get_world_position() const;
        sf::Transform get_world_transform() const;
        const std::vector<Ptr> &get_children() const;

        template<typename T>
        T *get_component(const std::string &name);
        sf::Uint64 get_UID() const;
        void set_world(World* p_world);
        void set_world_position(sf::Vector2f position);

        void destroy() override;

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void draw_self(sf::RenderTarget &target, sf::RenderStates states) const;
        void remove_destroyed_components();
    private:
        sf::Uint64 m_uid;

        std::vector<std::unique_ptr<Component>> m_pending_components;
        std::vector<std::unique_ptr<Component>> m_components;
        std::vector<sf::Drawable *> m_drawables;

        std::vector<Ptr> m_children;
        Entity *m_parent;
        World* m_world;
    };

    template <typename T>
    void Entity::add_component(std::unique_ptr<T>& component) {
        Component::Ptr c(static_cast<Component *>(component.release()));

        switch (c->type()){
            case Component::Type::Drawable:
                m_drawables.push_back(dynamic_cast<sf::Drawable *>(c.get()));
                break;
            case Component::Type::Physics:
//                if (m_world)
//                    m_world->physics().add_body((dynamic_cast<PhysicsComponent*>(c.get()))->body);
//                else
//                    Logger::error("Entity::add_component", "Can't add physics component without world");
                break;
            case Component::Type::Script:break;
        }
        c->set_parent_UID(m_uid);
        c->on_start(*this);
        m_pending_components.push_back(std::move(c));
    }

    template<typename T>
    T *Entity::get_component(const std::string &name)  {
        if (name.empty()) return nullptr;
        auto result = std::find_if(m_components.begin(), m_components.end(), [&name](const Component::Ptr &c) {
            Logger::notify(c->get_name());
            return (c->get_name() == name);
        });

        if (result == m_components.end()) {
            result = std::find_if(m_pending_components.begin(), m_pending_components.end(),
                                  [&name](const Component::Ptr &c) { return (c->get_name() == name); }
            );
            if (result == m_pending_components.end()) return nullptr;
        }
        return dynamic_cast<T *>(result->get());
    }
}

#endif //YOSAI_ENTITY_HPP
