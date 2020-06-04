//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_MATERIALS_HPP
#define YOSAI_MATERIALS_HPP

#include <Kigen/physics/Models.hpp>

using kigen::Material;

namespace Data {
inline const Material iron = {
        .density = 500.f,
        .restitution = 0.2,
        .static_friction = 2.5f,
        .dynamic_friction = 0.5f
};

    inline const Material super_solid = {
            .density = 0.f,
            .restitution = 0,
            .static_friction = 100000.f,
            .dynamic_friction = 100000.5f
    };

}
#endif //YOSAI_MATERIALS_HPP
