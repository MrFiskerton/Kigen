//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 07.06.2020.
//

#include "Kigen/world/physics/shape/Polygon.hpp"

namespace kigen {
    Polygon::Polygon(std::vector<sf::Vector2f>& points) : m_points(points){
        ConvexHull::Graham_scan(m_points);
        init_area_inertia_centroid();
        init_face_normals();

        set_vertices(m_points);
    };

    void Polygon::set_vertices(const std::vector<sf::Vector2f> &convex_hull) {
        //m_vertices.append(sf::Vector2f{0.f, 0.f}); //centroid for TriangleFan
        for(const auto& position : convex_hull) m_vertices.append(sf::Vertex(position));
        m_vertices.append(m_points[0]); // closing
        m_vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);
        for (std::size_t i = 0; i < vertex_count(); i++) m_vertices[i].color = sf::Color::Yellow;
    }

    Shape::Type Polygon::type() const { return Type::Polygon; }

    void Polygon::init_area_inertia_centroid() {
        // See https://en.wikipedia.org/wiki/Polygon
        // See https://en.wikipedia.org/wiki/Second_moment_of_area
        // See https://en.wikipedia.org/wiki/Centroid
        // See https://www.physicsforums.com/threads/calculating-polygon-inertia.25293/
        const float _1_div_6 = 1.f / 6.f;
        sf::Vector2f centroid{0.f, 0.f};

        // Inertia calculation; Note: using mass in final, not density
        float scale, numerator{0.f}, denominator{0.f}, tmp;
        for (std::size_t i1 = 0u, i2 = 1u; i1 < m_points.size(); i1++, (i2 = i1 + 1 < m_points.size() ? i1 + 1 : 0)) {
            auto &p1 = m_points[i1];
            auto &p2 = m_points[i2];
            tmp = cross(p1, p2);

            //area += tmp; // Accumulate doubled triangle area

            centroid += (p1 + p2) * tmp;

            scale = dot(p1, p1) + dot(p1, p2) + dot(p2, p2);
            //Note: 2D cross return z length //tmp = std::sqrt(cross(p1, p2));
            numerator += tmp * scale;
            denominator += tmp; //Note: is equal to double area
        }
        m_area = 0.5f * denominator;

        centroid *= _1_div_6;
        centroid /= m_area;     // Note: using signed area
        m_area = std::abs(m_area);

        m_inertia = 0.f;
        if (!is_almost_zero(denominator)) {
            m_inertia = numerator / denominator;
            m_inertia /= 6.f;
        }

        // Make the centroid (0, 0)  in model space
        for (auto& point: m_points) point -= centroid;
    }

    void Polygon::init_face_normals() {
        for (std::size_t i1 = 0u, i2 = 1u; i1 < m_points.size(); i1++, (i2 = i1 + 1 < m_points.size() ? i1 + 1 : 0)) {
            auto face = m_points[i2] - m_points[i1];
            assertion(!is_almost_zero(length(face)), "Zero-length edge!");
            // Calculate normal with 2D cross product between vector and scalar
            m_normals.emplace_back(sf::Vector2f(face.y, -face.x));
            normalize(m_normals[i1]);
        }
    }

    sf::Vector2f Polygon::get_support(sf::Vector2f &direction) {
        // The extreme point along a direction within a polygon
        sf::Vector2f* best_point = &m_points[0];
        float projection, best_projection = dot(*best_point, direction);
        for(auto& point: m_points) {
            projection = dot(point, direction);
            if (projection > best_projection) {
                best_projection = projection;
                best_point = &point;
            }
        }
        return *best_point;
    }

    void Polygon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(m_vertices, states);
    }

    std::size_t Polygon::vertex_count() const { m_vertices.getVertexCount(); }

    sf::FloatRect Polygon::bounds() const { m_vertices.getBounds(); }
}
