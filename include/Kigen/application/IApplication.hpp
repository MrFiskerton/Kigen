//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#ifndef INCLUDED_APPLICATION_HPP
#define INCLUDED_APPLICATION_HPP

#include <SFML/System/Time.hpp>

namespace kigen {
    class IApplication {
        friend struct DefaultApplicationLoop;
    public:
        IApplication() = default;
        virtual ~IApplication() = default;

        virtual bool is_runing() = 0;

    protected:
        virtual void update_input() = 0;
        virtual void update_logic(const sf::Time &deltaTime) = 0;
        virtual void update_graphics() = 0;
        virtual void render() = 0;
    };
} //namespace kigen

#endif //INCLUDED_APPLICATION_HPP
