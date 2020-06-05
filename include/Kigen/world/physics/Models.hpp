//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#ifndef YOSAI_MODELS_HPP
#define YOSAI_MODELS_HPP

#include <SFML/System.hpp>

namespace kigen {

    struct MassDependedComponent {
        float mass{0.f};          // == 0 is inf mass
        float inverse_mass{0.f};

        // For rotations
        float inertia{0.f};
        float inverse_inertia{0.f};

        bool is_infinite() { return inverse_mass == 0.f; }
    };

    struct Material {
        using Ptr = std::shared_ptr<Material>;

        float density{0.f};
        float restitution{0.f};      // упругость
        float static_friction{0.f};
        float dynamic_friction{0.f};
    };

    struct LinearComponent {
        sf::Vector2f position{0.f, 0.f};
        sf::Vector2f velocity{0.f, 0.f};
        float acceleration{0.f};
    };

    struct AngularComponent { // Угловые компоненты
        float orientation{0.f}; // в радианах
        float velocity{0.f};
        float torque{0.f};
    };


}


#endif //YOSAI_MODELS_HPP
