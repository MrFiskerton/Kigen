//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 05.06.2020.
//

#ifndef YOSAI_RANDOM_HPP
#define YOSAI_RANDOM_HPP

#include <cassert>
#include <random>
#include <ctime>
#include <SFML/System/Vector2.hpp>
#include <Kigen/world/physics/Math.hpp>

float random(float from, float to);
int   random(int   from, int   to);

sf::Vector2f random_direction(float from_r = 0.f, float to_r = _2_PI);

#endif //YOSAI_RANDOM_HPP
