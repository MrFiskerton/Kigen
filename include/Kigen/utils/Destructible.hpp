//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 03.06.2020.
//

#ifndef YOSAI_DESTRUCTIBLE_HPP
#define YOSAI_DESTRUCTIBLE_HPP

#include <algorithm>
#include <functional>

namespace kigen {
    class Destructible {
    public:
        Destructible() : m_is_destroyed{false} {}

        virtual ~Destructible() = default;

        virtual void destroy() { m_is_destroyed = true; };

        bool is_destroyed() const { return m_is_destroyed; };

        /*template<template<typename, typename> class Container, typename T, typename A = std::allocator<T> >
        void remove_destroyed(Container<T, A> &container, std::function<void(const T&)>eraser) {
            container.erase(std::remove_if(container.begin(), container.end(), [&](const T &p) {
                if (p->is_destroyed()) {
                    eraser(p);
                    return true;
                }
                return false;
            }), container.end());
        }*/

    private:
        bool m_is_destroyed;
    };
}

#endif //YOSAI_DESTRUCTIBLE_HPP
