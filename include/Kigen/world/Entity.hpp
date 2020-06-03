//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_ENTITY_HPP
#define YOSAI_ENTITY_HPP


#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <Kigen/utils/NonCopyable.hpp>
#include <vector>

#include "Component.hpp"
#include "World.hpp"

namespace kigen {
    class Entity final : public sf::Transformable, public sf::Drawable, private NonCopyable, public Destructible {
    public:
        using Ptr = std::unique_ptr<Entity>;

        explicit Entity();

        void update(float dt);

        void add_child(Ptr &child);
        void add_component(Component::Ptr &component);

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


    template<typename T>
    T *Entity::get_component(const std::string &name)  {
        if (name.empty()) return nullptr;
        auto result = std::find_if(m_components.begin(), m_components.end(), [&name](const Component::Ptr &c) {
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
