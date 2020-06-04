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
    return a.x * a.x + a.y * a.y;
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
    if (AlmostEqual2sComplement(l, 0.f, 16)) l = 1.f;
    float inv_len = 1.0f / l;
    return a *= inv_len;
}

float dot(const sf::Vector2f &a, const sf::Vector2f &b) {
    return a.x * b.x + a.y * b.y;
}

// Векторное произведение двух векторов возвращает скаляр
float cross(const sf::Vector2f &a, const sf::Vector2f &b) {
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
