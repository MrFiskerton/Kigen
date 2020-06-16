//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#include <Kigen/world/physics/Collision.hpp>

namespace kigen {

    void CollisionCircleAndCircle(Manifold& m){
        auto& A = *m.A;
        auto& B = *m.B;
        const float radius_A = reinterpret_cast<Circle *>(A.shape().get())->radius;
        const float radius_B = reinterpret_cast<Circle *>(B.shape().get())->radius;

        // Вектор от A к B
        sf::Vector2f n = B.lin().position - A.lin().position;
        float r = radius_A + radius_B;

        float squared_distance = squared_length(n);
        if (squared_distance > sqr(r)) {
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
            m.penetration = radius_A;
            m.normal = random_direction(); // Случайно выбрано
        }
        m.contacts[0] = m.normal * radius_A + A.lin().position;
    }
}