//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#ifndef YOSAI_MATH_HPP
#define YOSAI_MATH_HPP

#include <SFML/Audio.hpp>
#include <cmath>
#include <cassert>

inline const float PI = 3.141592653589793238463f;
inline const float _180_div_PI = 180.f / PI;
inline const float _2_PI = 2 * PI;

float to_degrees(float radians);
float to_degrees(const sf::Vector2f& a);
int round_degrees(float degrees);

bool AlmostEqual2sComplement(float A, float B, unsigned int maxULPs);
bool is_almost_zero(float a);
bool is_almost_zero(const sf::Vector2f& a);

float sqr(float a);
float squared_length(const sf::Vector2f &a);
float length(const sf::Vector2f &a);
float squared_distance(const sf::Vector2f &a, const sf::Vector2f &b);

float distance(const sf::Vector2f &a, const sf::Vector2f &b);

sf::Vector2f& normalize(sf::Vector2f &a);

float dot(const sf::Vector2f &a, const sf::Vector2f &b);

float cross(const sf::Vector2f &a, const sf::Vector2f &b);
sf::Vector2f cross(const sf::Vector2f &a, float s) ;
sf::Vector2f cross(float s, const sf::Vector2f &a);


#endif //YOSAI_MATH_HPP
