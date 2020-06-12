//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#ifndef YOSAI_COLLISION_HPP
#define YOSAI_COLLISION_HPP

#include <Kigen/utils/Random.hpp>
#include <Kigen/world/physics/Manifold.hpp>
#include "Kigen/world/physics/shape/Circle.hpp"
#include <Kigen/world/physics/shape/Polygon.hpp>

namespace kigen {
    void CollisionCircleAndCircle(Manifold& m);
    void CollisionCircleAndPolygon(Manifold& m);
    void CollisionPolygonAndCircle(Manifold& m);
    void CollisionPolygonAndPolygon(Manifold& m);

    typedef void (*CollisionSolver)(Manifold& m);
    extern const CollisionSolver collision_solver[Shape::SIZE][Shape::SIZE];
}


#endif //YOSAI_COLLISION_HPP
