//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 09.06.2020.
//

#ifndef YOSAI_PHYSICSLAW_HPP
#define YOSAI_PHYSICSLAW_HPP

#include <memory>
#include <functional>
#include <utility>
#include "Kigen/world/physics/PhysicsScene.hpp"

namespace kigen {
    class PhysicsLaw {
    public:
        using Law = std::function<void(PhysicsScene &)>;

        PhysicsLaw(std::string law_name, Law law) : name(std::move(law_name)), m_law(std::move(law)) {}
        void operator ()(PhysicsScene & scene) { m_law(scene); }
    public:
        const std::string name;
    private:
        Law m_law;
    };


    extern PhysicsLaw energy_loss;
    extern PhysicsLaw gravitation;
    extern PhysicsLaw const_gravity;

}

#endif //YOSAI_PHYSICSLAW_HPP
