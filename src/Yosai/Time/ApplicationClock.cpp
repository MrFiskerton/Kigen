//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#include "Yosai/Time/ApplicationClock.hpp"

ApplicationClock::ApplicationClock():m_realTotalTime(sf::Time::Zero), m_clock() {}

sf::Time ApplicationClock::frame_time() {
    auto dtime = m_clock.restart();
    m_realTotalTime += dtime;

    // Hard bound: dt should not exeed 50ms (20fps)
    if (dtime.asMilliseconds() > 50) {
        Logger::warn("ApplicationClock::frame_time")
                << "Frame time just exceeded 50ms and is set down to 50ms. Its time was (ms): "
                << std::to_string(dtime.asMilliseconds()) << "." << Logger::endl;
        return sf::milliseconds(50);
    } else {
        return dtime;
    }
}


sf::Time ApplicationClock::total_elapced_time() const {
    return m_realTotalTime + m_clock.getElapsedTime();
}

void ApplicationClock::reset() {
    m_clock.restart();
    m_realTotalTime = sf::Time::Zero;
}
