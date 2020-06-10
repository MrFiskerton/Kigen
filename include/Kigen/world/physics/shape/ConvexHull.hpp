//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 10.06.2020.
//

#ifndef YOSAI_CONVEXHULL_HPP
#define YOSAI_CONVEXHULL_HPP

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <Kigen/world/physics/Math.hpp>
#include <Kigen/utils/Assertion.hpp>

namespace kigen {
    class ConvexHull {
    public:
        static void Graham_scan(std::vector<sf::Vector2f>& points);
    private:
        static sf::Vector2f& top_right(std::vector<sf::Vector2f>& points);
        static void sort(std::vector<sf::Vector2f>& points, sf::Vector2f& p0);
        static void remove_redundant_colinear(std::vector<sf::Vector2f>& points, sf::Vector2f& p0);
        static void build_hull(std::vector<sf::Vector2f>& points);
    };
}

#endif //YOSAI_CONVEXHULL_HPP
