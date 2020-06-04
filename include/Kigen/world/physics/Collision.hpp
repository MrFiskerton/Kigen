//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#ifndef YOSAI_COLLISION_HPP
#define YOSAI_COLLISION_HPP


#include "Kigen/world/physics/shape/Circle.hpp"

namespace kigen {
    class Manifold;
    void CollisionCircleAndCircle(Manifold& m);
}


#endif //YOSAI_COLLISION_HPP
