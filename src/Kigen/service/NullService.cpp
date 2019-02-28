//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.02.19.
//

#include <Kigen/service/NullService.hpp>

namespace {
    kigen::NullCamera camera;
}

namespace kigen {
    // Specialization
    template<> IService *null_service<ICamera>() { return &camera; }
}