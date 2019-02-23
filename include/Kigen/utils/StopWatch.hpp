//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 14.07.18.
//

#ifndef INCLUDED_STOPWATCH_HPP
#define INCLUDED_STOPWATCH_HPP

#include <SFML/System/Clock.hpp>

class StopWatch {
public:
    StopWatch();
    ~StopWatch() = default;

    sf::Time elapsed_time() const;

    bool is_running() const;

    void start();

    void pause();

    void reset();

    void restart();

private:
    bool      m_running;
    sf::Clock m_clock;
    sf::Time  m_elapsed_buffer;
};


#endif //INCLUDED_STOPWATCH_HPP
