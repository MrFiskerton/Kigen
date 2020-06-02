//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#ifndef YOSAI_MATH_HPP
#define YOSAI_MATH_HPP

#include <SFML/Audio.hpp>
#include <cmath>
#include <cassert>

inline const float PI = 3.14159265358979f;

bool AlmostEqual2sComplement(float A, float B, unsigned int maxULPs) {
    //ULP (Units in the Last Place)
    //See  https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
    //     https://habr.com/ru/post/112953/

    /*
     * ULP - это максимальное количество чисел с плавающей запятой, которое может лежать между проверяемым и ожидаемым
     * значением. Другой смысл этой переменной – это количество двоичных разрядов (начиная с младшего) в сравниваемых
     * числах разрешается упустить. Например, maxUlps=16, означает, что младшие 4 бита  могут не совпадать, а числа все
     * равно будут считаться равными.
     * */

    // maxULPs не должен быть отрицательным и не слишком большим, чтобы NaN не был равен ни одному числу
    assert(maxULPs > 0 && maxULPs < 4 * 1024 * 1024);
    int aInt = *(int *) &A;
    int bInt = *(int *) &B;

    // Уберем знак в aInt, если есть, чтобы получить правильно упорядоченную последовательность
    if (aInt < 0) aInt = 0x80000000 - aInt;
    if (bInt < 0) bInt = 0x80000000 - bInt;

    unsigned int intDiff = abs(aInt - bInt);
    return intDiff <= maxULPs;
}

static float sqr(float a) { return  a * a;}

static float squared_length(const sf::Vector2f &a) {
    return a.x * a.x + a.y * a.y;
}

static float length(const sf::Vector2f &a) {
    return std::sqrt(squared_length(a));
}

static float squared_distance(const sf::Vector2f &a, const sf::Vector2f &b) {
    return squared_length(a - b);
}

static float distance(const sf::Vector2f &a, const sf::Vector2f &b) {
    return std::sqrt(squared_distance(a, b));
}

static sf::Vector2f& normalize(sf::Vector2f &a) {
    return a /= length(a);
}

static float dot(const sf::Vector2f &a, const sf::Vector2f &b) {
    return a.x * b.x + a.y * b.y;
}

// Векторное произведение двух векторов возвращает скаляр
static float cross(const sf::Vector2f &a, const sf::Vector2f &b) {
    return a.x * b.y - a.y * b.x;
}

// Более экзотичные (но необходимые) виды векторных произведений
// с вектором a и скаляром s, оба возвращают вектор
sf::Vector2f cross(const sf::Vector2f &a, float s) {
    return {s * a.y, -s * a.x};
}

sf::Vector2f cross(float s, const sf::Vector2f &a) {
    return {-s * a.y, s * a.x};
}

#endif //YOSAI_MATH_HPP
