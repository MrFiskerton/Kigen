//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.03.19.
//

#ifndef YOSAI_KEYACTIONTYPE_HPP
#define YOSAI_KEYACTIONTYPE_HPP

namespace kigen {

enum KeyActionType : unsigned char {
    RealTime = 1u,
    Pressed = 1u << 1,
    Released = 1u << 2
};

}

#endif //YOSAI_KEYACTIONTYPE_HPP 
