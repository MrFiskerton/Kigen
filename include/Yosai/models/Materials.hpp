//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_MATERIALS_HPP
#define YOSAI_MATERIALS_HPP

#include <Kigen/world/physics/Models.hpp>
#include <memory>

using kigen::Material;

namespace Data {
    inline const auto iron = std::make_shared<Material>(Material{
            .density = 100.f,
            .restitution = 0.2,
            .static_friction = 2.5f,
            .dynamic_friction = 0.5f
    });

    inline const auto super_solid = std::make_shared<Material>(Material{
            .density = 0.f,
            .restitution = 0,
            .static_friction = 100000.f,
            .dynamic_friction = 100000.5f
    });

}
#endif //YOSAI_MATERIALS_HPP
