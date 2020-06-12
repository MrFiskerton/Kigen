//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 06.06.2020.
//

#ifndef YOSAI_POLYGON_HPP
#define YOSAI_POLYGON_HPP

#include <Kigen/world/physics/shape/ConvexHull.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <utility>
#include "Shape.hpp"

namespace kigen {
    class Manifold;
    class Polygon : public Shape {
        friend void CollisionCircleAndPolygon(Manifold& m);
    public:
        explicit Polygon(std::vector<sf::Vector2f>& points);

        Type type() const override;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        sf::Vector2f get_support(const sf::Vector2f& direction);
    private:
        std::size_t vertex_count() const;
        void init_area_inertia_centroid();
        void init_face_normals();
        void set_vertices(const std::vector<sf::Vector2f>& convex_hull);
        sf::FloatRect bounds() const;
        std::size_t next_i(std::size_t i) const;
    protected:
        std::vector<sf::Vector2f> m_points;
        std::vector<sf::Vector2f> m_normals;

        sf::VertexArray m_vertices; // Drawable
    };
}

#endif //YOSAI_POLYGON_HPP
