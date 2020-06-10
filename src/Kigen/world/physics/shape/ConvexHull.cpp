//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 10.06.2020.
//

#include "Kigen/world/physics/shape/ConvexHull.hpp"

namespace kigen {
    void ConvexHull::Graham_scan(std::vector<sf::Vector2f> &points) {
        // Time complexity O(n log n)
        // See https://habr.com/ru/post/144921/
        assertion(points.size() > 2, "Array of points has less than 2 points, convex hull is not possible");
        std::swap(top_right(points), points[0]);
        sf::Vector2f &p0 = points[0];
        sort(points, p0);
        remove_redundant_colinear(points, p0);
        assertion(points.size() > 2, "Array of points has less than 2 points, convex hull is not possible");
        build_hull(points);
    }

    sf::Vector2f &ConvexHull::top_right(std::vector<sf::Vector2f> &points) {
        sf::Vector2f *current = &points[0];
        for (std::size_t i = 1; i < points.size(); i++) {
            if (points[i].x > current->x) current = &points[i];
            else if ((points[i].x == current->x) && (points[i].y < current->y)) current = &points[i];
        }
        return *current;
    }

    void ConvexHull::sort(std::vector<sf::Vector2f> &points, sf::Vector2f &p0) {
        std::sort(std::next(points.begin()), points.end(), [p0](const sf::Vector2f &p1, const sf::Vector2f &p2) {
            sf::Vector2f e1 = p1 - p0;
            sf::Vector2f e2 = p2 - p0;
            int o = orientation(e1, e2);

            if (o == -1) return false;  // Anti-clockwise orientation
            // e vectors are on same line therefor want to record vertex farthest along that line
            if (o == 0) return squared_length(e2) > squared_length(e1);
        });
    }

    void ConvexHull::remove_redundant_colinear(std::vector<sf::Vector2f> &points, sf::Vector2f &p0) {
        // If two or more points make same angle with p0, Remove all but the one that is farthest from p0
        std::size_t m = 1; // Initialize size of modified array
        for (std::size_t i = 1; i < points.size(); i++) {
            // Keep removing i while angle of i and i+1 is same with respect to p0
            while (i < points.size() - 1 && orientation(p0, points[i], points[i + 1]) == 0) i++;
            points[m++] = points[i];
        }
        points.resize(m);
    }

    void ConvexHull::build_hull(std::vector<sf::Vector2f> &points) {
        std::size_t last = 2; // 0, 1, 2  == 3;   // Process remaining n-3 points
        for (std::size_t i = 3; i < points.size(); i++) {
            while (orientation(points[last - 1], points[last], points[i]) != -1) last--;
            points[++last] = points[i];
        }
        points.resize(last + 1);
    }
}
