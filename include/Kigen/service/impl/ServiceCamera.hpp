//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 27.02.19.
//

#ifndef YOSAI_SERVICECAMERA_HPP
#define YOSAI_SERVICECAMERA_HPP

#include "../interface/ICamera.hpp"

namespace kigen {

class Camera : public ICamera {
public:
    void test() override { Logger::info() << "Camera Work" << Logger::endl; }
};


}

#endif //YOSAI_SERVICECAMERA_HPP
