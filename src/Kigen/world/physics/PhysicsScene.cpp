//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.06.2020.
//

#include <Kigen/world/physics/PhysicsScene.hpp>

namespace kigen {
    using namespace physics;

    void PhysicsScene::update(float dt) {
        // Why is dt/2  ?
        // See https://web.archive.org/web/20120624003417/http://www.niksula.hut.fi/~hkankaan/Homepages/gravity.html
        collision_check();
        for(auto& body: m_bodies) integrate_force(*body, dt * 0.5f);
        for(auto& contact: m_collisions) contact.apply_impulse();
        for(auto& body: m_bodies) {
            integrate_velocity(*body, dt);
            integrate_force(*body, dt * 0.5f);
        }
        for(auto& contact: m_collisions) contact.positional_correction();
        clear_state();
    }

    void PhysicsScene::collision_check() {
        for_body_pairs([&](PhysicsBody &A, PhysicsBody &B) {
            if (A.is_static() && B.is_static()) return;
            Manifold m(&A, &B);
            if (m.solve()) m_collisions.emplace_back(m);
        });
    }

    void PhysicsScene::integrate_force(RigidBody &body, float dt) {
        if (body.is_static()) return;
        body.lin().velocity += (body.lin().force * body.inverse_mass()) * dt;           // V' = V + a * dt; a = F / m;
        body.ang().velocity += (body.ang().torque * body.inverse_inertia()) * dt;
    }

    void PhysicsScene::integrate_velocity(RigidBody &body, float dt) {
        if (body.is_static()) return;
        body.lin().position    += body.lin().velocity * dt;                              // x' = x + V * dt;
        body.ang().orientation += body.ang().velocity * dt;
    }

    void PhysicsScene::clear_state() {
        //Remove any destroyed bodies //TODO

        for(auto& body: m_bodies) body->clean_applied_force();
        m_collisions.clear();
    }

    void PhysicsScene::add_body(PhysicsBody::Ptr &body) {  m_bodies.push_back(body.get());  }

    void PhysicsScene::for_body_pairs(const std::function<void(PhysicsBody &A, PhysicsBody &B)>& f) {
        for (auto it_A = m_bodies.begin(); it_A != m_bodies.end(); it_A++) {
            for (auto it_B = std::next(it_A); it_B != m_bodies.end(); it_B++) {
                f(*(*it_A), *(*it_B));
            }
        }
    }

    void PhysicsScene::for_body(const std::function<void(PhysicsBody &A)> &f) {
        for(auto& body: m_bodies) f(*body);
    }
}


