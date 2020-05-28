//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.02.19.
//

#ifndef YOSAI_ICAMERA_HPP
#define YOSAI_ICAMERA_HPP

#include <Kigen/utils/locator/IService.hpp>

namespace kigen {

class ICamera : public IService {
public:
    virtual void test() = 0;
};

class NullCamera : public ICamera {
public:
    void test() override { Logger::info() << "NULL camera Work" << Logger::endl; }
};

} // namespace kigen
#endif //YOSAI_ICAMERA_HPP 
