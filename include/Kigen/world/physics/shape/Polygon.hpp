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
        explicit Polygon(sf::VertexArray vertices) : m_vertices(std::move(vertices)) {
            assert(!(vertex_count() & 1u)); // Even
            m_vertices.setPrimitiveType(sf::PrimitiveType::Lines);
        };

        Type type() const override { return Type::Polygon; }

        void compute_mass(float density, MassDependedComponent &result) const override {
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
            float area = 0.5f * denominator;

            centroid *= _1_div_6;
            centroid /= area;     // Note: using signed area

            float inertia = 0.f;
            if (!is_almost_zero(denominator)) {
                inertia = numerator / denominator;
                inertia /= 6.f;
            }
            result.compute_mass(std::abs(area), density);
            result.compute_inertia(inertia);

            // Make the centroid (0, 0)  in model space
//            for(std::size_t i = 0u; i < vertex_count(); i++) m_vertices[i].position -= centroid; //TODO WTF? Call const reference
        }

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            target.draw(m_vertices, states);
        }

    private:
        std::size_t vertex_count() const { m_vertices.getVertexCount(); }
        sf::FloatRect bounds() const { m_vertices.getBounds();}
    protected:
        sf::VertexArray m_vertices;
        sf::Vector2f m_normals;
    };
}


//
//    void SetOrient( real radians )
//    {
//        u.Set( radians );
//    }
//
//    void Draw( void ) const
//    {
//        glColor3f( body->r, body->g, body->b );
//        glBegin( GL_LINE_LOOP );
//        for(uint32 i = 0; i < m_vertexCount; ++i)
//        {
//            Vec2 v = body->position + u * m_vertices[i];
//            glVertex2f( v.x, v.y );
//        }
//        glEnd( );
//    }
//
//    Type GetType( void ) const
//    {
//        return ePoly;
//    }
//
//    // Half width and half height
//    void SetBox( real hw, real hh )
//    {
//        m_vertexCount = 4;
//        m_vertices[0].Set( -hw, -hh );
//        m_vertices[1].Set(  hw, -hh );
//        m_vertices[2].Set(  hw,  hh );
//        m_vertices[3].Set( -hw,  hh );
//        m_normals[0].Set(  0.0f,  -1.0f );
//        m_normals[1].Set(  1.0f,   0.0f );
//        m_normals[2].Set(  0.0f,   1.0f );
//        m_normals[3].Set( -1.0f,   0.0f );
//    }
//
//    void Set( Vec2 *vertices, uint32 count )
//    {
//        // No hulls with less than 3 vertices (ensure actual polygon)
//        assert( count > 2 && count <= MaxPolyVertexCount );
//        count = std::min( (int32)count, MaxPolyVertexCount );
//
//        // Find the right most point on the hull
//        int32 rightMost = 0;
//        real highestXCoord = vertices[0].x;
//        for(uint32 i = 1; i < count; ++i)
//        {
//            real x = vertices[i].x;
//            if(x > highestXCoord)
//            {
//                highestXCoord = x;
//                rightMost = i;
//            }
//
//                // If matching x then take farthest negative y
//            else if(x == highestXCoord)
//                if(vertices[i].y < vertices[rightMost].y)
//                    rightMost = i;
//        }
//
//        int32 hull[MaxPolyVertexCount];
//        int32 outCount = 0;
//        int32 indexHull = rightMost;
//
//        for (;;)
//        {
//            hull[outCount] = indexHull;
//
//            // Search for next index that wraps around the hull
//            // by computing cross products to find the most counter-clockwise
//            // vertex in the set, given the previos hull index
//            int32 nextHullIndex = 0;
//            for(int32 i = 1; i < (int32)count; ++i)
//            {
//                // Skip if same coordinate as we need three unique
//                // points in the set to perform a cross product
//                if(nextHullIndex == indexHull)
//                {
//                    nextHullIndex = i;
//                    continue;
//                }
//
//                // Cross every set of three unique vertices
//                // Record each counter clockwise third vertex and add
//                // to the output hull
//                // See : http://www.oocities.org/pcgpe/math2d.html
//                Vec2 e1 = vertices[nextHullIndex] - vertices[hull[outCount]];
//                Vec2 e2 = vertices[i] - vertices[hull[outCount]];
//                real c = Cross( e1, e2 );
//                if(c < 0.0f)
//                    nextHullIndex = i;
//
//                // Cross product is zero then e vectors are on same line
//                // therefor want to record vertex farthest along that line
//                if(c == 0.0f && e2.LenSqr( ) > e1.LenSqr( ))
//                    nextHullIndex = i;
//            }
//
//            ++outCount;
//            indexHull = nextHullIndex;
//
//            // Conclude algorithm upon wrap-around
//            if(nextHullIndex == rightMost)
//            {
//                m_vertexCount = outCount;
//                break;
//            }
//        }
//
//        // Copy vertices into shape's vertices
//        for(uint32 i = 0; i < m_vertexCount; ++i)
//            m_vertices[i] = vertices[hull[i]];
//
//        // Compute face normals
//        for(uint32 i1 = 0; i1 < m_vertexCount; ++i1)
//        {
//            uint32 i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
//            Vec2 face = m_vertices[i2] - m_vertices[i1];
//
//            // Ensure no zero-length edges, because that's bad
//            assert( face.LenSqr( ) > EPSILON * EPSILON );
//
//            // Calculate normal with 2D cross product between vector and scalar
//            m_normals[i1] = Vec2( face.y, -face.x );
//            m_normals[i1].Normalize( );
//        }
//    }
//
//    // The extreme point along a direction within a polygon
//    Vec2 GetSupport( const Vec2& dir )
//    {
//        real bestProjection = -FLT_MAX;
//        Vec2 bestVertex;
//
//        for(uint32 i = 0; i < m_vertexCount; ++i)
//        {
//            Vec2 v = m_vertices[i];
//            real projection = Dot( v, dir );
//
//            if(projection > bestProjection)
//            {
//                bestVertex = v;
//                bestProjection = projection;
//            }
//        }
//
//        return bestVertex;
//    }
//
//
//};


#endif //YOSAI_POLYGON_HPP
