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
        explicit Polygon(sf::VertexArray vertices);

        Type type() const override;

        void initialize();

        void compute_mass(float density, MassDependedComponent &result) const override;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        std::size_t vertex_count() const;
        sf::FloatRect bounds() const;
    protected:
        sf::VertexArray m_vertices;
        sf::Vector2f m_normals;
        float m_area, m_inertia; //TODO move up
    };
}

#endif //YOSAI_POLYGON_HPP
