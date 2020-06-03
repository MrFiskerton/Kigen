//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.06.2020.
//

#include "Kigen/physics/PhysicsScene.hpp"

namespace kigen {
    void PhysicsScene::for_body_pairs(const std::function<void(RigidBody &A, RigidBody &B)>& f) {
        for (auto it_A = m_bodies.begin(); it_A != m_bodies.end(); it_A++) {
            for (auto it_B = std::next(it_A); it_B != m_bodies.end(); it_B++) {
                f(*(*it_A), *(*it_B));
            }
        }
    }

    void PhysicsScene::update(float dt) {
        make_contacts();

        law_of_gravitation();

        // Why is dt/2  ?
        // See https://web.archive.org/web/20120624003417/http://www.niksula.hut.fi/~hkankaan/Homepages/gravity.html
        for(auto& body: m_bodies) intergate_force(*body, dt * 0.5f);
        for(auto& contact: m_contacts) contact.apply_impulse();
        for(auto& body: m_bodies) {
            integrate_velocity(*body, dt);
            intergate_force(*body, dt * 0.5f);
        }
        for(auto& contact: m_contacts) contact.positional_correction();
        clear_state();
    }

    void PhysicsScene::make_contacts() {
        for_body_pairs([&](RigidBody &A, RigidBody &B) {
            if (A.m_mass.is_infinite() && B.m_mass.is_infinite()) return;
            Manifold m(A, B);
            if (m.solve()) m_contacts.emplace_back(m);
        });
    }

    void PhysicsScene::law_of_gravitation() {
        const float G = 6.67f; //TODO
        const float MIN_DISTANCE = 100.f;
        for_body_pairs([&](RigidBody &A, RigidBody &B) {
            if (A.m_mass.is_infinite() && B.m_mass.is_infinite()) return;

            sf::Vector2f delta = B.m_lin.position - A.m_lin.position;
            float r = length(delta);
            if (r > MIN_DISTANCE) return; // isn't close enough

            sf::Vector2f force = normalize(delta) * G * A.m_mass.mass * B.m_mass.mass / sqr(r);
            A.apply_force(force);
            B.apply_force(-force);
        });
    }

    void PhysicsScene::intergate_force(RigidBody &body, float dt) {
        if (body.m_mass.is_infinite()) return;
        body.m_lin.velocity += (body.m_force * body.m_mass.inverse_mass) * dt;           // V' = V + a * dt; a = F / m;
        body.m_ang.velocity += (body.m_ang.torque * body.m_mass.inverse_inertia) * dt;
    }

    void PhysicsScene::integrate_velocity(RigidBody &body, float dt) {
        if (body.m_mass.is_infinite()) return;
        body.m_lin.position += body.m_lin.velocity * dt;                                 // x' = x + V * dt;
        body.m_ang.orientation += body.m_ang.velocity * dt;
    }

    void PhysicsScene::clear_state() {
        //Remove any destroyed bodies
//        m_bodies.erase(std::remove_if(m_bodies.begin(), m_bodies.end(),
//                [](const RigidBody* p) {  return p->is_destroyed(); }), m_bodies.end());

        for(auto& body: m_bodies) {
            body->m_force = {0.f, 0.f};
            body->m_ang.torque = 0.f;
        }
        m_contacts.clear();
    }

    void PhysicsScene::add_body(RigidBody::Ptr &body) {
        m_bodies.push_back(std::move(body));
    }
}


