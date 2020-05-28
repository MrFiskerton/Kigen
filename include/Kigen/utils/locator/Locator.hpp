//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 23.02.19.
//

#ifndef INCLUDED_KIGEN_SERVICELOCATOR_HPP
#define INCLUDED_KIGEN_SERVICELOCATOR_HPP

#include <vector>
#include <Kigen/input/InputControl.hpp>
#include "NullService.hpp"

namespace kigen {

class Locator {
public:
    template<class T>
    static void registrate();

    template<class T>
    static void provide(T *service);

    template<class T>
    static T &locate();

private:
    Locator() = default;

    ~Locator() = default;

    template<class T>
    static bool is_registered();

private:
    class service_registrator {
        static std::size_t counter;
    public:
        template<typename T>
        static std::size_t id() {
            static std::size_t value = counter++;
            return value;
        }
    };

private:
    static std::vector<IService *> m_services;
};

} //namespace kigen

#include "./Locator.inl"

#endif //INCLUDED_KIGEN_SERVICELOCATOR_HPP
