//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#include <Yosai/Application.hpp>

int main(int argc, char *argv[]) {
    try {
        Application::instance().run();
    } catch (std::exception &e) {
        std::cerr << "\n>>> EXCEPTION: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknow excepton caught!" << std::endl;
    }
    return EXIT_SUCCESS;
}