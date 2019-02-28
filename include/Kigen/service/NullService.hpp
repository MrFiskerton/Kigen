//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.02.19.
//

#ifndef YOSAI_NULLSERVICE_HPP
#define YOSAI_NULLSERVICE_HPP

#include "Services.hpp"

namespace kigen {
    template<class T>
    IService* null_service() {
        Logger::warn() << "Service with typeid = " << typeid(T).name()
                       << " hasn't null object implimentation." << Logger::endl;
        return nullptr;
    }

    template<>
    IService* null_service<ICamera>();
}

#endif //YOSAI_NULLSERVICE_HPP 
