//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.02.19.
//

#ifndef YOSAI_NULLSERVICE_HPP
#define YOSAI_NULLSERVICE_HPP

#include "IService.hpp"

namespace kigen {
namespace locator {

    template<class T>
    IService *null_service() {
        Logger::warn("null_service") << "Service with typeid = " << typeid(T).name()
                                     << " hasn't null object implimentation." << Logger::endl;
        return nullptr;
    }

//    template<>
//    IService *null_service<SInputControl>();

} // namespace locator
} // namespace kigen


#endif //YOSAI_NULLSERVICE_HPP 
