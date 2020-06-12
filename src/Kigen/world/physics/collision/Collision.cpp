//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.06.2020.
//

#include <Kigen/world/physics/Collision.hpp>

namespace kigen {
    CollisionSolver const collision_solver[Shape::SIZE][Shape::SIZE] = {
             {CollisionCircleAndCircle,     CollisionCircleAndPolygon},
             {CollisionPolygonAndCircle,    CollisionPolygonAndPolygon}
    };
}