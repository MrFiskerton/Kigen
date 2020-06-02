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
#include "RigidBody.hpp"

namespace kigen {

    class PhysicsScene final {
    public:
        enum Layer : unsigned {
            L1 = 0, L2
        };

        void update(float dt);

    private:
        void intergate_force(RigidBody& body, float dt);
        void integrate_velocity(RigidBody& body, float dt);
        void for_body_pairs(const std::function<void(RigidBody& A, RigidBody& B)>& f);
        void clear_state();
    private:
        std::list<RigidBody> m_bodies;
        std::vector<Manifold> m_contacts;
    };

}


#endif //YOSAI_PHYSICSSCENE_HPP
