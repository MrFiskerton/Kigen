//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#include "Kigen/graphics/Vector.hpp"

namespace kigen {
    Vector::Vector(): line(sf::Lines, 2), arrow(5.f, 3) {
        arrow.setOrigin(arrow.getRadius()/* * 0.5f*/, arrow.getRadius() * 0.5f); //TODO Самый край стрелки немного выступает

        arrow.setFillColor(sf::Color::Blue);
        line[0].color = sf::Color::Blue;
        line[1].color = sf::Color::Blue; //TODO WTF! ПОчему не меняется из белого ?
    }

    void Vector::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        if(is_almost_zero(line[1].position - line[0].position)) return;

        target.draw(line, states);
        target.draw(arrow, states);
    }

    void Vector::from(const sf::Vector2f &from) {
        line[0].position = from;
    }

    void Vector::to(const sf::Vector2f &to) {
        line[1] = to;
        arrow.setPosition(to);
        //Logger::notify() << to_degrees(to - line[0].position) << "\n";
        arrow.setRotation(90.f + to_degrees(to - line[0].position));
    }
}