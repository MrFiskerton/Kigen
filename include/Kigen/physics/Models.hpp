//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#ifndef YOSAI_MODELS_HPP
#define YOSAI_MODELS_HPP

#include <SFML/System.hpp>

namespace kigen {

    struct MassDependedComponent {
        float mass;          // == 0 is inf mass
        float inverse_mass;

        // For rotations
        float inertia;
        float inverse_inertia;

        bool is_infinite() { return inverse_mass == 0.f; }
    };

    struct Material {
        float density;
        float restitution;      // упругость
        float static_friction;
        float dynamic_friction;
    };

    struct LinearComponent {
        sf::Vector2f position{0.f, 0.f};
        sf::Vector2f velocity{0.f, 0.f};
        float acceleration{0.f};
    };

    struct AngularComponent { // Угловые компоненты
        float orientation; // в радианах
        float velocity;
        float torque;
    };


}


#endif //YOSAI_MODELS_HPP
