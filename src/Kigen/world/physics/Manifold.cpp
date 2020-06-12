//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#include <Kigen/utils/Logger.hpp>
#include <Kigen/world/physics/Manifold.hpp>
#include <Kigen/world/message/Message.hpp>

namespace kigen {
    using namespace physics;
    
    bool Manifold::solve() {
        collision_solver[A->shape()->type()][B->shape()->type()](*this);

        bool is_contacted = (contact_count > 0);
        if (is_contacted) initialize();
        return is_contacted;
    }

    void Manifold::apply_impulse() {
        if (A->is_static() && B->is_static()) {
            infinite_mass_correction();
            return;
        }

        for (std::size_t i = 0; i < contact_count; ++i) {
            sf::Vector2f ra = contacts[i] - A->lin().position;
            sf::Vector2f rb = contacts[i] - B->lin().position;

            // Relative velocity
            const sf::Vector2f rv = (B->lin().velocity + cross(B->ang().velocity, rb))
                                  - (A->lin().velocity + cross(A->ang().velocity, ra));

            // Relative velocity along the normal
            float contact_v = dot(rv, normal);

            // Do not resolve if velocities are separating
            if (contact_v > 0) return;

            // Calculate impulse scalar j
            float a_rotation_component = sqr(cross(ra, normal)) * A->inverse_inertia();
            float b_rotation_component = sqr(cross(rb, normal)) * B->inverse_inertia();
            float denominator = A->inverse_mass() + B->inverse_mass()
                               + a_rotation_component + b_rotation_component;

            // Impulse scalar
            float j = -(1.0f + m_elasticity) * contact_v;
            j /= denominator;
            j /= (float) contact_count;

            // Don'tangent apply tiny impulses
            if (is_almost_zero(j)) {
                // Apply impulse
                sf::Vector2f impulse = j * normal;
                A->apply_impulse(-impulse, ra);
                B->apply_impulse(impulse, rb);
            }

// =================== Friction impulse ================================ //
            // Вычисляем касательный вектор
            sf::Vector2f tangent = normalize(rv - (normal * dot(rv, normal)));

            // Вычисляем величину, прилагаемую вдоль вектора трения
            float jt = -dot(rv, tangent);
            jt /= denominator; //TODO!
            jt /= (float) contact_count;

            // Don'tangent apply tiny friction impulses
            if (is_almost_zero(jt)) return;

            // Amontons' - Coulomb's Law of dry friction: Fтр <= mu Fn,
            // Fn aka N; = j * normal,  Fтр == jt, m_static_friction aka mu
            // See https://en.wikipedia.org/wiki/Friction#Dry_friction
            sf::Vector2f tangent_impulse = ((std::abs(jt) < m_friction_S * j) ? jt : (-j * m_friction_D)) * tangent;

            // Apply friction impulse
            A->apply_impulse(-tangent_impulse, ra);
            B->apply_impulse( tangent_impulse, rb);
        }
    }

    void Manifold::positional_correction() {
        float k = std::max(penetration - PENETRATION_ALLOWANCE, 0.0f);
        k /= (A->inverse_mass() + B->inverse_mass());
        sf::Vector2f correction = normal * k * PENETRATION_CORRECTION_PERCENTAGE;
        A->lin().position += -correction * A->inverse_mass(); // Note: don't forget minus
        B->lin().position +=  correction * B->inverse_mass();
    }

    void Manifold::infinite_mass_correction() {
        A->stop();
        B->stop();
    }

    void Manifold::initialize() {
        // Calculate average restitution
        m_elasticity = std::min(A->material().restitution, B->material().restitution);

        // Calculate static and dynamic friction
        m_friction_S = std::sqrt(A->material().static_friction * B->material().static_friction);
        m_friction_D = std::sqrt(A->material().dynamic_friction * B->material().dynamic_friction);

        Message msg = {.type = Message::Type::Physics,
                       .physics = Message::PhysicsEvent(this)};
        A->send_message(msg);
    }

}
