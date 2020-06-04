//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#include <Kigen/world/physics/Collision.hpp>
#include <Kigen/world/physics/Manifold.hpp>

namespace kigen {

    void CollisionCircleAndCircle(Manifold& m){
        auto& A = m.A;
        auto& B = m.B;
        auto circle_A = reinterpret_cast<Circle *>(A.m_shape.get());
        auto circle_B = reinterpret_cast<Circle *>(B.m_shape.get());

        // Вектор от A к B
        sf::Vector2f n = B.m_lin.position - A.m_lin.position;
        float r = circle_A->radius + circle_B->radius;

        float squared_distance = squared_length(n);
        if (squared_distance > r * r) {
            m.contact_count = 0;
            return;
        }

        float distance = std::sqrt(squared_distance);

        // У окружностей распознана коллизия, вычисляем многообразие
        m.contact_count = 1;
        if (!is_almost_zero(distance)) {
            m.penetration = r - distance;
            m.normal = n / distance;
        } else {  // Окружности имеют одинаковое положение
            m.penetration = circle_A->radius;
            m.normal = {0.f, 1.f}; // Случайно выбрано
        }
        m.contacts[0] = m.normal * circle_A->radius + A.m_lin.position;
    }
}