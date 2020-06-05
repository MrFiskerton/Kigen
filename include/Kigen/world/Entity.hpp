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
#include <Kigen/utils/Next.hpp>

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
        void add_component(std::unique_ptr<T> &in_component);

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
        void insert_penting_components();
        void update_children(float dt);
    private:
        const sf::Uint64 m_uid;
        std::array<std::vector<Component::Ptr>, 2> m_pending_components;
        Next m_pending_frame;
        std::vector<Component::Ptr> m_components;
        std::vector<sf::Drawable *> m_drawables; // TODO list?

        std::vector<Ptr> m_children;
        Entity *m_parent;
        World* m_world;
    };

    template <typename T>
    void Entity::add_component(std::unique_ptr<T>& in_component) {
        Component::Ptr component(static_cast<Component *>(in_component.release()));
        m_pending_components[m_pending_frame].push_back(std::move(component));
    }

    template<typename T>
    T *Entity::get_component(const std::string &name)  {
        if (name.empty()) return nullptr;
        auto result = std::find_if(m_components.begin(), m_components.end(), [&name](const Component::Ptr &c) {
            Logger::notify(c->get_name());
            return (c->get_name() == name);
        });

        if (result == m_components.end()) {
            bool is_found = false;
            for (auto& pending_frame: m_pending_components) {
                result = std::find_if(pending_frame.begin(), pending_frame.end(),
                             [&name](const Component::Ptr &c) { return (c->get_name() == name); }
                );
                if (result != pending_frame.end()) { is_found = true; break; }
            }
            if (!is_found) return nullptr;  //TODO test it
        }
        return dynamic_cast<T *>(result->get());
    }
}

#endif //YOSAI_ENTITY_HPP
