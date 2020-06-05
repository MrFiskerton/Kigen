//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#ifndef YOSAI_MANIFOLD_HPP
#define YOSAI_MANIFOLD_HPP

#include "RigidBody.hpp"
#include <cmath>
#include "Collision.hpp"
#include "PhysicalConstants.hpp"

namespace kigen {
    class Manifold {
    public:
        Manifold(RigidBody& a, RigidBody& b) : A(a), B(b), contact_count(0u) {}
        bool solve();
        void apply_impulse();
        void positional_correction();
        void infinite_mass_correction();
        void initialize();
    public:
        RigidBody& A;
        RigidBody& B;

        float penetration;           // Depth of penetration from collision
        sf::Vector2f normal;         // From A to B
        sf::Vector2f contacts[2];    // Points of contact during collision
        std::size_t contact_count;   // Number of contacts that occured during collision
        float m_elasticity;                   // Mixed restitution
        float m_friction_D;                  // Mixed dynamic friction
        float m_friction_S;                  // Mixed static friction
    };
}

#endif //YOSAI_MANIFOLD_HPP
