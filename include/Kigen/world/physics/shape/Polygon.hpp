//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 06.06.2020.
//

#ifndef YOSAI_POLYGON_HPP
#define YOSAI_POLYGON_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <utility>
#include "Shape.hpp"

namespace kigen {
    class Polygon : public Shape {
    public:
        explicit Polygon(std::vector<sf::Vector2f> points);

        Type type() const override;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        std::size_t vertex_count() const;
        void initialize();
        std::vector<sf::Vector2f>& make_convex_hull(std::vector<sf::Vector2f>& points);
        sf::Vector2f& top_right(const std::vector<sf::Vector2f>& points);
        void set_vertices(const std::vector<sf::Vector2f>& convex_hull);
        sf::FloatRect bounds() const;
    protected:
        sf::VertexArray m_vertices;
        sf::Vector2f m_normals;
         //TODO move up
    };
}

#endif //YOSAI_POLYGON_HPP
