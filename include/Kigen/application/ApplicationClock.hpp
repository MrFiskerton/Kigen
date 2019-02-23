//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#ifndef INCLUDED_APPLICATIONTIME_HPP
#define INCLUDED_APPLICATIONTIME_HPP

#include <Kigen/utils/Utils.hpp>
#include <SFML/System/Clock.hpp>

namespace kigen {
    class ApplicationClock {
    public:
        ApplicationClock();
        virtual ~ApplicationClock() = default;

        sf::Time frame_time();
        sf::Time total_elapced_time() const;
        void reset();

    private:
        sf::Time m_realTotalTime;
        sf::Clock m_clock;
    };
} //namespace kigen
#endif //INCLUDED_APPLICATIONTIME_HPP
