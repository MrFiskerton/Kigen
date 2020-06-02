//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#ifndef YOSAI_MATH_HPP
#define YOSAI_MATH_HPP

#include <SFML/Audio.hpp>

inline const float  PI = 3.14159265358979f;

static float dot(const sf::Vector2f& a, const sf::Vector2f& b) {
    return a.x * b.x + a.y * b.y;
}

// Векторное произведение двух векторов возвращает скаляр
static float cross(const sf::Vector2f& a, const sf::Vector2f& b) {
    return a.x * b.y - a.y * b.x;
}

// Более экзотичные (но необходимые) виды векторных произведений
// с вектором a и скаляром s, оба возвращают вектор
sf::Vector2f cross(const sf::Vector2f& a, float s ) {
    return {s * a.y, -s * a.x };
}

sf::Vector2f cross(float s, const sf::Vector2f& a ) {
    return {-s * a.y, s * a.x};
}

#endif //YOSAI_MATH_HPP
