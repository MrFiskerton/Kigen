//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 05.06.2020.
//

#include "Kigen/utils/Random.hpp"

namespace {
    static std::default_random_engine random_engine(static_cast<unsigned long>(std::time(nullptr)));
}

float random(float from, float to) {
    //Produces random floating-point values i, uniformly distributed on the interval [a, b)
    assert(from < to);
    std::uniform_real_distribution<float> dist(from, to);
    return dist(random_engine);
}

int random(int from, int to) {
    assert(from < to);
    std::uniform_int_distribution<int> dist(from, to);
    return dist(random_engine);
}

sf::Vector2f random_direction(float from_r, float to_r) {
    return {std::cos(random(from_r, to_r)), std::sin(random(from_r, to_r))};
}