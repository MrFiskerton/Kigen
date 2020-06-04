//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#ifndef YOSAI_MANIFOLD_HPP
#define YOSAI_MANIFOLD_HPP

#include "RigidBody.hpp"
#include <cmath>

namespace kigen {
    class Manifold {
    public:
        Manifold(RigidBody& a, RigidBody& b) : A(a), B(b), m_contact_count(0u) {}
        bool solve();
        void solve(Type<Circle>, Type<Circle>);
        void apply_impulse();
        void positional_correction();
        void infinite_mass_correction();
        void initialize();
    private:
        RigidBody& A;
        RigidBody& B;

        float m_penetration;         // Depth of m_penetration from collision
        sf::Vector2f m_normal;       // From A to B
        sf::Vector2f m_contacts[2];  // Points of contact during collision
        std::size_t m_contact_count; // Number of m_contacts that occured during collision
        float m_e;                   // Mixed restitution
        float m_df;                  // Mixed dynamic friction
        float m_sf;                  // Mixed static friction
    };
}

#endif //YOSAI_MANIFOLD_HPP
