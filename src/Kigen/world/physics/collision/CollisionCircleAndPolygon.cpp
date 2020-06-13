//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 10.06.2020.
//

#include <Kigen/world/physics/Collision.hpp>

namespace kigen {

    void CollisionCircleAndPolygon(Manifold &m) {
        auto &A = *m.A;
        auto &B = *m.B;
        const float radius_A = reinterpret_cast<Circle *>(A.shape().get())->radius;
        const auto& polygon_B = *reinterpret_cast<Polygon *>(B.shape().get());

        m.contact_count = 0;

        // Transform circle center to Polygon model space
        sf::Vector2f center_A = B.to_model_space(A.lin().position);
        //------------------------------------------
        // Find edge with minimum penetration
        float separation = std::numeric_limits<float>::min();
        std::size_t face_normal_i = 0;
        for (std::size_t i = 0; i < polygon_B.m_points.size(); i++) {
            float s = dot(polygon_B.m_normals[i], center_A - polygon_B.m_points[i]);
            if (s > radius_A) return;
            if (s > separation) { separation = s; face_normal_i = i; }
        }
        //------------------------------------------
        // Grab face's vertices
        const sf::Vector2f& face_normal = polygon_B.m_normals[face_normal_i];
        sf::Vector2f face_p1 = polygon_B.m_points[face_normal_i];
        sf::Vector2f face_p2 = polygon_B.m_points[polygon_B.next_i(face_normal_i)];

        // Check to see if center_A is within polygon
        if (is_almost_zero(separation)) {
            m.penetration = radius_A;
            m.normal = -B.to_world_space(face_normal);
            m.contact_count = 1;
            m.contacts[0] = m.normal * radius_A + A.lin().position;
            return;
        }

        // Determine which voronoi region of the edge center of circle lies within
        m.penetration = radius_A - separation;
        float dot1 = dot(center_A - face_p1, face_p2 - face_p1);
        float dot2 = dot(center_A - face_p2, face_p1 - face_p2);

        auto closest_to = [&](const sf::Vector2f &v) {
            if (squared_distance(center_A, v) > sqr(radius_A)) return;
            m.contact_count = 1;
            m.contacts[0] = B.to_world_space(v);
            m.normal = normalize(B.to_world_space(v - center_A));
        };
        if (dot1 <= 0.0f) { closest_to(face_p1); return; }
        if (dot2 <= 0.0f) { closest_to(face_p2); return; }
        // Closest to face
        if (dot(center_A - face_p1, face_normal) > radius_A) return;

        m.normal = -B.to_world_space(face_normal);
        m.contact_count = 1;
        m.contacts[0] = m.normal * radius_A + A.lin().position;
    }

    void CollisionPolygonAndCircle(Manifold& m) {
        Logger::notify("C & P");
        std::swap(m.A, m.B);//TODO
        CollisionCircleAndPolygon(m);
        std::swap(m.A, m.B);
        m.normal = -m.normal;
    }
}