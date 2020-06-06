//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 07.06.2020.
//

#include "Kigen/world/physics/shape/Polygon.hpp"

namespace kigen {
    Polygon::Polygon(sf::VertexArray vertices) : m_vertices(std::move(vertices)) {
        m_vertices.append(m_vertices[0]);

        m_vertices.setPrimitiveType(sf::PrimitiveType::LinesStrip);
        for (std::size_t i = 0; i < vertex_count(); i++) m_vertices[i].color = sf::Color::Yellow;
        initialize();
    };

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
        for(std::size_t i = 0u; i < vertex_count(); i++) m_vertices[i].position -= centroid;
    }

    void Polygon::compute_mass(float density, MassDependedComponent &result) const {
        result.compute_mass(m_area, density);
        result.compute_inertia(m_inertia);
    }

    void Polygon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(m_vertices, states);
    }

    std::size_t Polygon::vertex_count() const { m_vertices.getVertexCount(); }

    sf::FloatRect Polygon::bounds() const { m_vertices.getBounds(); }
}
