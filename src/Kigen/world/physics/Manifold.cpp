//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#include <Kigen/utils/Logger.hpp>
#include <Kigen/world/physics/Manifold.hpp>

namespace kigen {
    using namespace physics;
    
    bool Manifold::solve() {
        CollisionCircleAndCircle(*this);//(A.m_shape->type(), B.m_shape->type());

        bool is_contacted = (contact_count > 0);
        if (is_contacted) initialize();
        return is_contacted;
    }

    void Manifold::apply_impulse() {
        if (A.m_mass.is_infinite() && B.m_mass.is_infinite()) {
            infinite_mass_correction();
            return;
        }

        for (std::size_t i = 0; i < contact_count; ++i) {
            sf::Vector2f ra = contacts[i] - A.m_lin.position;
            sf::Vector2f rb = contacts[i] - B.m_lin.position;

            // Relative velocity
            sf::Vector2f rv = (B.m_lin.velocity + cross(B.m_ang.velocity, rb))
                            - (A.m_lin.velocity + cross(A.m_ang.velocity, ra));

            // Relative velocity along the normal
            float contact_v = dot(rv, normal);

            // Do not resolve if velocities are separating
            if (contact_v > 0) return;

            // Calculate impulse scalar j
            float a_rotation_component = sqr(cross(ra, normal)) * A.m_mass.inverse_inertia;
            float b_rotation_component = sqr(cross(rb, normal)) * B.m_mass.inverse_inertia;
            float denominator = A.m_mass.inverse_mass + B.m_mass.inverse_mass
                               + a_rotation_component + b_rotation_component;

            // Impulse scalar
            float j = -(1.0f + m_elasticity) * contact_v;
            j /= denominator;
            j /= (float) contact_count;

            // Don'tangent apply tiny impulses
            if (is_almost_zero(j)) {
                // Apply impulse
                sf::Vector2f impulse = j * normal;
                A.apply_impulse(-impulse, ra);
                B.apply_impulse(impulse, rb);
            }

// =================== Friction impulse ================================ //
            rv = (B.m_lin.velocity + cross(B.m_ang.velocity, rb))
               - (A.m_lin.velocity + cross(A.m_ang.velocity, ra));


            // Вычисляем касательный вектор
            sf::Vector2f tangent = rv - (normal * dot(rv, normal));
            normalize(tangent);

            // Вычисляем величину, прилагаемую вдоль вектора трения
            float jt = -dot(rv, tangent);
            jt /= denominator; //TODO!
            jt /= (float) contact_count;

            // Don'tangent apply tiny friction impulses
            if (is_almost_zero(jt)) return;

            // Amontons' - Coulomb's Law of dry friction: Fтр <= mu Fn,
            // Fn aka N; = j * normal,  Fтр == jt
            // See https://en.wikipedia.org/wiki/Friction#Dry_friction

            //                                            m_static_friction aka mu
            sf::Vector2f tangent_impulse = ((std::abs(jt) < m_friction_S * j) ? jt : (-j * m_friction_D)) * tangent;

            // Apply friction impulse
            A.apply_impulse(-tangent_impulse, ra);
            B.apply_impulse( tangent_impulse, rb);
        }
    }

    void Manifold::positional_correction() {
        float k = (std::max(penetration - PENETRATION_ALLOWANCE, 0.0f)
                / (A.m_mass.inverse_mass + B.m_mass.inverse_mass));
        sf::Vector2f correction = normal * k * PENETRATION_CORRECTION_PERCENTAGE;
        A.m_lin.position -= correction * A.m_mass.inverse_mass;
        B.m_lin.position += correction * B.m_mass.inverse_mass;
    }

    void Manifold::infinite_mass_correction() {
        A.m_lin.velocity = {0.f, 0.f};
        B.m_lin.velocity = {0.f, 0.f};
    }

    void Manifold::initialize() {
        // Calculate average restitution
        m_elasticity = std::min(A.m_material->restitution, B.m_material->restitution);

        // Calculate static and dynamic friction
        m_friction_S = std::sqrt(A.m_material->static_friction * B.m_material->static_friction);
        m_friction_D = std::sqrt(A.m_material->dynamic_friction * B.m_material->dynamic_friction);

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
//            //if (rv.LenSqr() < (dt * gravity).LenSqr() + EPSILON) m_elasticity = 0.0f;
//        }
    }

}
