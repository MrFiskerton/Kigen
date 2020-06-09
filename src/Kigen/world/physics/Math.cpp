//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#include <Kigen/world/physics/Math.hpp>

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

bool is_almost_zero(float a, unsigned int maxULPs) {
    return AlmostEqual2sComplement(a, 0.f, maxULPs);
}

bool is_almost_zero(const sf::Vector2f& a) {
    return is_almost_zero(length(a));
}

bool is_even(std::size_t a) {
    return !(a & 1u);
}

int orientation(const sf::Vector2f& edge1, const sf::Vector2f& edge2) {
    float c = cross(edge1, edge2);
    if (is_almost_zero(c)) return 0;    // colinear
    if (c < 0.f) return -1;             // anti-clockwise orientation
    return 1;                           // clockwise orientation
}

int orientation(const sf::Vector2f& p1, const sf::Vector2f& p0, const sf::Vector2f& p2){
    return orientation(p1 - p0, p2 - p0);
}

float to_degrees(float radians) {
    return radians * _180_div_PI;
}

float to_degrees(const sf::Vector2f& a) {
    return to_degrees(atan2f(a.y, a.x));
}

int round_degrees(float degrees) {
    return int(360.f + roundf(degrees)) % 360;
}

float sqr(float a) { return  a * a;}

float squared_length(const sf::Vector2f &a) {
    return dot(a, a);
}

float length(const sf::Vector2f &a) {
    return std::sqrt(squared_length(a));
}

float squared_distance(const sf::Vector2f &a, const sf::Vector2f &b) {
    return squared_length(a - b);
}

float distance(const sf::Vector2f &a, const sf::Vector2f &b) {
    return std::sqrt(squared_distance(a, b));
}

sf::Vector2f& normalize(sf::Vector2f &a) {
    float l = length(a);
    if (!is_almost_zero(l)) {
        float inv_len = 1.0f / l;
        a *= inv_len;
    }
    return a; ;
}

float dot(const sf::Vector2f &a, const sf::Vector2f &b) {
    return a.x * b.x + a.y * b.y;
}

// Векторное произведение двух 2D векторов возвращает скаляр
float cross(const sf::Vector2f &a, const sf::Vector2f &b) {
    return a.x * b.y - a.y * b.x;
}

// Более экзотичные (но необходимые) виды векторных произведений
// С вектором a и скаляром s, оба возвращают вектор
sf::Vector2f cross(const sf::Vector2f &a, float s) {
    return {s * a.y, -s * a.x};
}

sf::Vector2f cross(float s, const sf::Vector2f &a) {
    return {-s * a.y, s * a.x};
}
