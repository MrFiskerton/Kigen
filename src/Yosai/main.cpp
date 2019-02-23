//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#include <Yosai/Yosai.hpp>
#include <iostream>
#include <Kigen/application/DefaultApplicationLoop.hpp>

int main(int argc, char *argv[]) {
    try {
        Yosai instance;
        kigen::DefaultApplicationLoop::run(instance);
    } catch (std::exception &e) {
        std::cerr << "\n>>> EXCEPTION: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknow excepton caught!" << std::endl;
    }
    return EXIT_SUCCESS;
}