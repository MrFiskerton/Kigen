//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#include <Kigen/world/component/Component.hpp>
#include <Kigen/world/Entity.hpp>


#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace {
    sf::Uint64 vacant_uid = 1u; //use 0 for no entity
}

namespace kigen {
    Entity::Entity(MessageBus& mbus) : Communicable(mbus),
                       m_uid(vacant_uid++),
                       m_pending_frame(0, 1),
                       m_parent(nullptr),
                       m_world(nullptr) {}

    void Entity::add_child(Entity::Ptr &child) {
        child->m_parent = this;
        child->set_world(m_world);
        m_children.push_back(std::move(child));
    }

    Entity::Ptr Entity::remove_child(Entity &child) {
        auto result = std::find_if(m_children.begin(), m_children.end(), [&child](const Ptr &p) {
            return (p.get() == &child);
        });

        if (result != m_children.end()) {
            Ptr found = std::move(*result);
            found->m_parent = nullptr;
            found->m_world = nullptr;
            m_children.erase(result);
            return found;
        }
        return nullptr;
    }

    const std::vector<Entity::Ptr> &Entity::get_children() const {
        return m_children;
    }

    sf::Vector2f Entity::get_world_position() const {
        return get_world_transform() * sf::Vector2f();
    }

    sf::Transform Entity::get_world_transform() const {
        auto t = sf::Transform::Identity;
        for (const auto *p_entity = this; p_entity != nullptr; p_entity = p_entity->m_parent)
            t = p_entity->getTransform() * t;

        return t;
    }

    void Entity::set_world_position(sf::Vector2f position) {
        if (m_parent) position -= m_parent->get_world_position();
        setPosition(position);
    }

    void Entity::remove_destroyed_components() {
        m_components.erase(std::remove_if(m_components.begin(), m_components.end(), [&](const Component::Ptr &p) {
            if (p->is_destroyed()) {
                if (p->type() == Component::Type::Drawable) {
                    auto r = std::find(m_drawables.begin(), m_drawables.end(), dynamic_cast<sf::Drawable *>(p.get()));
                    if (r != m_drawables.end()) m_drawables.erase(r);
                }
                return true;
            }
            return false;
        }), m_components.end());
    }

    void Entity::update(float dt) {
        remove_destroyed_components();
        for (auto &c : m_components) c->entity_update(*this, dt);
        insert_penting_components();
        //mark self as deleted if no components remain
        if (m_components.empty()) { destroy();}
        update_children(dt);
    }

    void Entity::receive_message(const Message &message) {
        for (auto& component : m_components) component->receive_message(message);
        for (auto& child: m_children) child->receive_message(message);
    }

    void Entity::insert_penting_components() {
        //Copy any new components we may have aquired via update
        std::size_t current = m_pending_frame;
        m_pending_frame.next();  // Change add_component context for avoid loops
        for (auto &component : m_pending_components[current]) {
            switch (component->type()){
                case Component::Type::Drawable:
                    m_drawables.push_back(dynamic_cast<sf::Drawable *>(component.get()));
                    break;
                case Component::Type::Physics:
//                if (m_world)
//                    m_world->physics().add_body((dynamic_cast<PhysicsBody*>(component.get()))->body);
//                else
//                    Logger::error("Entity::add_component", "Can't add physics component without world");
                    break;
                case Component::Type::Script:break;
            }
            component->set_owner_UID(m_uid);
            component->on_attach(*this);
            component->set_message_bus(*m_message_bus);
            m_components.push_back(std::move(component));
        }
        m_pending_components[current].clear();
    }

    void Entity::update_children(float dt) {
        std::vector<Entity *> dead_children;
        for (auto &c : m_children) {
            c->update(dt);
            if (c->is_destroyed()) dead_children.push_back(&(*c));
        }
        for (const auto &dc : dead_children) remove_child(*dc);
    }

    sf::Uint64 Entity::get_UID() const { return m_uid; }

    void Entity::destroy() {
        Destructible::destroy();
        for (auto& component : m_components) component->destroy();
        for (auto& child : m_children) child->m_parent = nullptr; //TODO children
    }

    void Entity::set_world(World *p_world) {
        m_world = p_world;
        for (auto& c : m_children) c->set_world(p_world);
    }

    void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        for (const auto& c : m_children) target.draw(*c, states);
        draw_self(target, states);
    }

    void Entity::draw_self(sf::RenderTarget &target, sf::RenderStates states) const {
        for (const auto& d : m_drawables) target.draw(*d, states);
    }


}

