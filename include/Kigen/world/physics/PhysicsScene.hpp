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
#include "PhysicsConstants.hpp"
#include <Kigen/utils/Logger.hpp>

namespace kigen {

    class PhysicsScene final {
    public:
        void update(float dt);
        void add_body(PhysicsBody::Ptr& body);
        void for_body_pairs(const std::function<void(PhysicsBody& A, PhysicsBody& B)>& f);
        void for_body(const std::function<void(PhysicsBody& A)>& f);
        void clear_state();
        const std::vector<Manifold>& get_collisions() const;
    private:
        void collision_check();
        void integrate_force(RigidBody& body, float dt);
        void integrate_velocity(RigidBody& body, float dt);
    private:
        std::list<PhysicsBody*> m_bodies;
        std::vector<Manifold> m_collisions;
    };

}


#endif //YOSAI_PHYSICSSCENE_HPP
