//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 07.06.2020.
//

#include <stack>
#include "Kigen/world/physics/shape/Polygon.hpp"

namespace kigen {
    Polygon::Polygon(std::vector<sf::Vector2f> points) {
        set_vertices(make_convex_hull(points));

        initialize();
    };

    void Polygon::set_vertices(const std::vector<sf::Vector2f> &convex_hull) {
        for(const auto& position : convex_hull) m_vertices.append(sf::Vertex(position));
        m_vertices.append(m_vertices[0]);
        m_vertices.setPrimitiveType(sf::PrimitiveType::LinesStrip);
        for (std::size_t i = 0; i < vertex_count(); i++) m_vertices[i].color = sf::Color::Yellow;
    }

    Shape::Type Polygon::type() const { return Type::Polygon; }

    void Polygon::initialize() {
        // See https://en.wikipedia.org/wiki/Polygon
        // See https://en.wikipedia.org/wiki/Second_moment_of_area
        // See https://en.wikipedia.org/wiki/Centroid
        // See https://www.physicsforums.com/threads/calculating-polygon-inertia.25293/
        const float _1_div_6 = 1.f / 6.f;
        sf::Vector2f centroid{0.f, 0.f};

        // Inertia calculation; Note: using mass in final, not density
        float scale, numerator{0.f}, denominator{0.f}, tmp;
        for (std::size_t i1 = 0u, i2 = 0u; i1 < vertex_count(); i1++, (i2 = i1 + 1 < vertex_count() ? i1 + 1 : 0)) {
            auto &p1 = m_vertices[i1].position;
            auto &p2 = m_vertices[i2].position;
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
        for (std::size_t i = 0u; i < vertex_count(); i++) m_vertices[i].position -= centroid;
    }

    void Polygon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(m_vertices, states);
    }

    std::size_t Polygon::vertex_count() const { m_vertices.getVertexCount(); }

    sf::FloatRect Polygon::bounds() const { m_vertices.getBounds(); }

    std::vector<sf::Vector2f>& Polygon::make_convex_hull(std::vector<sf::Vector2f> &points) {
        assert(points.size() > 2);

        std::swap(top_right(points), points[0]);
        sf::Vector2f& p0 =points[0];

        std::sort(std::next(points.begin()), points.end(), [&](const sf::Vector2f& p1, const sf::Vector2f& p2) {
            sf::Vector2f e1 = p1 - p0;
            sf::Vector2f e2 = p2 - p0;
            int o = orientation(e1, e2);

            if (o == -1) return false;  // Anti-clockwise orientation
            // e vectors are on same line therefor want to record vertex farthest along that line
            if (o == 0) return squared_length(e2) > squared_length(e1);
        });

        // If two or more points make same angle with p0, Remove all but the one that is farthest from p0
        std::size_t m = 1; // Initialize size of modified array
        for (std::size_t i = 1; i < points.size(); i++) {
            // Keep removing i while angle of i and i+1 is same with respect to p0
            while (i < points.size() - 1 && orientation(p0, points[i], points[i + 1]) == 0) i++;
            points[m++] = points[i];
        }
        points.resize(m);

        // If modified array of points has less than 2 points, convex hull is not possible
        assert(points.size() > 2);

        std::size_t last = 2; // 0, 1, 2  == 3;   // Process remaining n-3 points
        for (std::size_t i = 3; i < points.size(); i++) {
            while (orientation(points[last - 1], points[last], points[i]) != -1) last--;
            points[++last] = points[i];
        }
        points.resize(last + 1);
        return points;
    }

    sf::Vector2f &Polygon::top_right(const std::vector<sf::Vector2f> &points) {
        sf::Vector2f const *current = &points[0];
        for (std::size_t i = 1; i < points.size(); i++) {
            if (points[i].x > current->x) {
                current = &points[i];
            } else if ((points[i].x == current->x) && (points[i].y < current->y)) {
                current = &points[i];
            }
        }
        return *const_cast<sf::Vector2f *>(current);
    }
}
