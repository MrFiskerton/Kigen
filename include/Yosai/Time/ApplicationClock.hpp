//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#ifndef INCLUDED_APPLICATIONTIME_HPP
#define INCLUDED_APPLICATIONTIME_HPP

#include <Yosai/Util/Util.hpp>
#include <SFML/System/Clock.hpp>

class ApplicationClock {
public:
    ApplicationClock();
    virtual ~ApplicationClock() = default;

    sf::Time frame_time();
    sf::Time total_elapced_time() const;
    void reset();
private:
    sf::Time  m_realTotalTime;
    sf::Clock m_clock;
};

#endif //INCLUDED_APPLICATIONTIME_HPP
