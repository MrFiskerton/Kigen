//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#ifndef YOSAI_PHYSICALCONSTANTS_HPP
#define YOSAI_PHYSICALCONSTANTS_HPP

namespace physics {
    // PhysicsScene::law_of_gravitation
    inline const float G = 6.67f * 1e-2; //TODO Gravity scale
    inline const float GRAVITY_MIN_DISTANCE = 500.f;

    // Manifold::positional_correction
    inline const float PENETRATION_ALLOWANCE = 0.05f;            // обычно от 0.01 до 0.1
    inline const float PENETRATION_CORRECTION_PERCENTAGE = 0.4f; // обычно от 20% до 80%

}

#endif //YOSAI_PHYSICALCONSTANTS_HPP