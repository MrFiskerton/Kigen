//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_MATERIALS_HPP
#define YOSAI_MATERIALS_HPP

#include <Kigen/world/physics/Models.hpp>
#include <memory>

using kigen::Material;

namespace Data {
    inline const auto static_material = std::make_shared<Material>(Material{
            .density = 0.f,
            .restitution = 0.f,
            .static_friction = 0.f,
            .dynamic_friction = 0.f
    });


    inline const auto steel = std::make_shared<Material>(Material{
            .density = 50.f,
            .restitution = 0.8f,
            .static_friction = 0.574f,
            .dynamic_friction = 0.542f
    });

    inline const auto super_solid = std::make_shared<Material>(Material{
            .density = 1000.f,
            .restitution = 0.5,
            .static_friction = 0.1f,
            .dynamic_friction = 0.15f
    });

}
#endif //YOSAI_MATERIALS_HPP
