//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.06.2020.
//

#include "Kigen/physics/PhysicsScene.hpp"

namespace kigen {
    void PhysicsScene::for_body_pairs(const std::function<void(RigidBody &A, RigidBody &B)>& f) {
        for (auto it_A = m_bodies.begin(); it_A != m_bodies.end(); it_A++) {
            for (auto it_B = std::next(it_A); it_B != m_bodies.end(); it_B++) {
                f(*it_A, *it_B);
            }
        }
    }

    void PhysicsScene::update(float dt) {
        clear_state();
        for_body_pairs([&](RigidBody &A, RigidBody &B) {
            if (A.m_mass.is_infinite() && B.m_mass.is_infinite()) return;
            Manifold m(A, B);
            if (m.solve()) m_contacts.emplace_back(m);
        });

        for(auto& body: m_bodies) intergate_force(body, dt * 0.5f);
        for(auto& contact: m_contacts) contact.apply_impulse();
        for(auto& body: m_bodies) {
            integrate_velocity(body, dt);
            intergate_force(body, dt * 0.5f);
        }
        for(auto& contact: m_contacts) contact.positional_correction();
    }

    void PhysicsScene::intergate_force(RigidBody &body, float dt) {
        if (body.m_mass.is_infinite()) return;
        body.m_lin.velocity += (body.m_force * body.m_mass.inverse_mass) * dt;
        body.m_ang.velocity += (body.m_ang.torque * body.m_mass.inverse_inertia) * dt;
    }

    void PhysicsScene::integrate_velocity(RigidBody &body, float dt) {
        if (body.m_mass.is_infinite()) return;
        body.m_lin.position += body.m_lin.velocity * dt;
        body.m_ang.orientation += body.m_ang.velocity * dt;
    }

    void PhysicsScene::clear_state() {
        //Remove any destroyed bodies
//        m_bodies.erase(std::remove_if(m_bodies.begin(), m_bodies.end(),
//                [](const RigidBody* p) {  return p->isPendingDestruction(); }), m_bodies.end());

        for(auto& body: m_bodies) {
            body.m_force = {0.f, 0.f};
            body.m_ang.torque = 0.f;
        }
        m_contacts.clear();
    }
}


