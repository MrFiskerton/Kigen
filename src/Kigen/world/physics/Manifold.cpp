//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#include <Kigen/utils/Logger.hpp>
#include <Kigen/world/physics/Manifold.hpp>

namespace kigen {
    bool Manifold::solve() {
        CollisionCircleAndCircle(*this);//(A.m_shape->type(), B.m_shape->type());

        bool is_contacted = (contact_count > 0);
        if (is_contacted) initialize();
        return is_contacted;
    }

    void Manifold::apply_impulse() {
        // Early out and positional correct if both objects have infinite mass
        if (A.m_mass.is_infinite() && B.m_mass.is_infinite()) infinite_mass_correction();

        for (std::size_t i = 0; i < contact_count; ++i) {
            sf::Vector2f ra = contacts[i] - A.m_lin.position;
            sf::Vector2f rb = contacts[i] - B.m_lin.position;

            // Relative velocity
            sf::Vector2f rv = (B.m_lin.velocity + cross(B.m_ang.velocity, rb)) -
                              (A.m_lin.velocity + cross(A.m_ang.velocity, ra));

            // Relative velocity along the normal
            float contact_v = dot(rv, normal);

            // Do not resolve if velocities are separating
            if (contact_v > 0) return;

            // Calculate impulse scalar j
            float a_rotation_component = sqr(cross(ra, normal)) * A.m_mass.inverse_inertia;
            float b_rotation_component = sqr(cross(rb, normal)) * B.m_mass.inverse_inertia;
            float inverse_mass_sum = A.m_mass.inverse_mass + B.m_mass.inverse_mass;

            float j = -(1.0f + m_e) * contact_v;
            j /= (inverse_mass_sum + a_rotation_component + b_rotation_component);
            j /= (float) contact_count;

            // Apply impulse
            sf::Vector2f impulse = j * normal;
            A.apply_impulse(-impulse, ra);
            B.apply_impulse( impulse, rb);

            // Friction impulse
            rv = (B.m_lin.velocity + cross(B.m_ang.velocity, rb)) -
                 (A.m_lin.velocity + cross(A.m_ang.velocity, ra));

            sf::Vector2f t = rv - (normal * dot(rv, normal));
            normalize(t);

            // j tangent magnitude
            float jt = -dot(rv, t);
            jt /= inverse_mass_sum;
            jt /= (float) contact_count;

            // Don't apply tiny friction impulses
            if (AlmostEqual2sComplement(jt, 0.f, 16)) return;

            // Coulumb's law
            sf::Vector2f tangent_impulse;
            if (std::abs(jt) < j * m_sf)
                tangent_impulse = t * jt;
            else
                tangent_impulse = t * -j * m_df;

            // Apply friction impulse
            A.apply_impulse(-tangent_impulse, ra);
            B.apply_impulse( tangent_impulse, rb);
        }
    }

    void Manifold::positional_correction() {
        const float slop = 0.05f;   // Penetration allowance               // обычно от 0.01 до 0.1
        const float percent = 0.4f; // Penetration percentage to correct   // обычно от 20% до 80%

        float k = (std::max(penetration - slop, 0.0f) / (A.m_mass.inverse_mass + B.m_mass.inverse_mass)) * percent;
        sf::Vector2f correction = normal * k;
        A.m_lin.position -= correction * A.m_mass.inverse_mass;
        B.m_lin.position += correction * B.m_mass.inverse_mass;
    }

    void Manifold::infinite_mass_correction() {
        A.m_lin.velocity = {0.f, 0.f};
        B.m_lin.velocity = {0.f, 0.f};
    }

    void Manifold::initialize() {
        // Calculate average restitution
        m_e = std::min(A.m_material->restitution, B.m_material->restitution);

        // Calculate static and dynamic friction
        m_sf = std::sqrt(A.m_material->static_friction * B.m_material->static_friction);
        m_df = std::sqrt(A.m_material->dynamic_friction * B.m_material->dynamic_friction);

        //TODO
//        for (std::size_t i = 0; i < contact_count; ++i) {
//            // Calculate radii from COM to contact
//            sf::Vector2f ra = contacts[i] - A.m_lin.position;
//            sf::Vector2f rb = contacts[i] - B.m_lin.position;
//
//            sf::Vector2f rv = (B.m_lin.velocity + cross(B.m_ang.velocity, rb)) -
//                              (A.m_lin.velocity + cross(A.m_ang.velocity, ra));
//
//            // Determine if we should perform a resting collision or not
//            // The idea is if the only thing moving this object is gravity,
//            // then the collision should be performed without any restitution
//            //if (rv.LenSqr() < (dt * gravity).LenSqr() + EPSILON) m_e = 0.0f;
//        }
    }

}
