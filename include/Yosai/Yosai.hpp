//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 23.02.19.
//

#ifndef YOSAI_YOSAI_HPP
#define YOSAI_YOSAI_HPP

#include <Yosai/states/AllStates.hpp>
#include <Kigen/application/BasicApplication.hpp>

class Yosai final: public kigen::BasicApplication {
private:
    void init_state_control() override;
};


#endif //YOSAI_YOSAI_HPP