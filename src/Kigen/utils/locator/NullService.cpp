//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.02.19.
//

#include <Kigen/utils/locator/NullService.hpp>

namespace {
    kigen::NullCamera camera;
}

namespace kigen {
namespace locator {
    // Specialization
    template<>
    IService *null_service<ICamera>() { return &camera; }


} // namespace locator
} // namespace kigen