//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.06.2020.
//

#ifndef YOSAI_PHYSICSSCENE_HPP
#define YOSAI_PHYSICSSCENE_HPP

#include <SFML/System/Time.hpp>
#include <vector>
#include <list>
#include <functional>
#include "Manifold.hpp"
#include <Kigen/world/component/PhysicsBody.hpp>
#include "PhysicalConstants.hpp"
#include <Kigen/utils/Logger.hpp>

namespace kigen {

    class PhysicsScene final {
    public:
        void update(float dt);
        void add_body(PhysicsBody::Ptr& body);
        void for_body_pairs(const std::function<void(RigidBody& A, RigidBody& B)>& f);
        void for_body(const std::function<void(RigidBody& A)>& f);
        std::list<PhysicsBody*>& bodies();
    private:
        void make_contacts();
        void intergate_force(RigidBody& body, float dt);
        void integrate_velocity(RigidBody& body, float dt);
        void clear_state();
    private:
        std::list<PhysicsBody*> m_bodies;
        std::vector<Manifold> m_contacts;
    };

}


#endif //YOSAI_PHYSICSSCENE_HPP
