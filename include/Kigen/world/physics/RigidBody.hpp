//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.06.2020.
//

#ifndef YOSAI_RIGIDBODY_HPP
#define YOSAI_RIGIDBODY_HPP

#include <Kigen/utils/Destructible.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Kigen/world/physics/shape/Shape.hpp"
#include "Models.hpp"

namespace kigen {
class RigidBody {
    public:
        using Ptr = std::shared_ptr<RigidBody>;
        RigidBody(const Shape::Ptr& shape, sf::Vector2f position, const Material::Ptr& material);
        void apply_force(const sf::Vector2f& force);
        void apply_impulse(const sf::Vector2f& impulse, const sf::Vector2f& contact_vector);
        void clean_applied_force();
        void stop();

        sf::Vector2f to_model_space(const sf::Vector2f& p);
        sf::Vector2f to_world_space(const sf::Vector2f& p);

        LinearComponent& lin() { return m_lin;};
        AngularComponent& ang() { return m_ang;};
        MassDependedComponent& m() { return m_mass; }
        const Material& material() const { return *m_material;}
        const Shape::Ptr& shape() const { return m_shape;}
        float inverse_mass() const { return m_mass.inverse_mass; };
        float inverse_inertia() const { return  m_mass.inverse_inertia; }
        bool is_static() const { return m_mass.is_infinite(); }

    private:
        void update_transform();
    protected:
        sf::Transform m_transform;
        sf::Transform m_inverse_transform;
        bool is_need_update_transform;

        sf::Vector2f m_impulse;
        LinearComponent m_lin;
        AngularComponent m_ang;

        Shape::Ptr m_shape;
        Material::Ptr m_material;
        MassDependedComponent m_mass;
    };
}


#endif //YOSAI_RIGIDBODY_HPP
