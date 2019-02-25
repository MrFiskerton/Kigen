//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 25.02.19.
//

#ifndef YOSAI_WINDOW_HPP
#define YOSAI_WINDOW_HPP


#include <SFML/Window.hpp>
#include <Kigen/input/InputControl.hpp>

namespace kigen {
    class Window : public sf::Window {
    public:
        InputControl input;
    };
}

#endif //YOSAI_WINDOW_HPP
