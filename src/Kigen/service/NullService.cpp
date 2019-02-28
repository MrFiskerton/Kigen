//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.02.19.
//

#include <Kigen/service/NullService.hpp>

namespace kigen {
    // Specialization
    template<>
    IService* null_service<ICamera>() {
        static NullCamera null_object;
        return &null_object;
//        static IService* null_object = new NullCamera;
//        return null_object;
    }
}