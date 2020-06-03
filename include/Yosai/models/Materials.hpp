//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_MATERIALS_HPP
#define YOSAI_MATERIALS_HPP

#include <Kigen/physics/Models.hpp>

using kigen::Material;

namespace Data {
inline const Material iron = {
        .density = 0.5f,
        .restitution = 0.5,
        .static_friction = 0.5f,
        .dynamic_friction = 0.5f
};
}
#endif //YOSAI_MATERIALS_HPP
