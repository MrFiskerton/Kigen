//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#include <Yosai/Yosai.hpp>
#include <cfenv>

int main(/*int argc, char *argv[]*/) {
    // Enable floating point exceptions
    // You'll get a SIGFPE when your NaN value is produced
    feenableexcept(FE_INVALID | FE_OVERFLOW);
    try {
        Yosai instance;
        kigen::default_loop(instance);
    } catch (std::exception &e) {
        std::cerr << "\n>>> EXCEPTION: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknow excepton caught!" << std::endl;
    }
    return EXIT_SUCCESS;
}