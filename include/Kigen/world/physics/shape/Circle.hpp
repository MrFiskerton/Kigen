//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#ifndef YOSAI_CIRCLE_HPP
#define YOSAI_CIRCLE_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include "Kigen/world/physics/shape/Shape.hpp"

namespace kigen{
    class Circle : public Shape {
    public:
        using Ptr = std::shared_ptr<Circle>;

        explicit Circle(float radius);
        Type type() const override;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override ;
    public: //TODO
        float radius;
    private:
        sf::CircleShape circle;
    };
}

#endif //YOSAI_CIRCLE_HPP
