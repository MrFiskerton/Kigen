//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#include "Yosai/ApplicationTime.hpp"

void ApplicationTime::update(const sf::Time &dtime) {
    m_realTotalTime += dtime;

    // Hard bound: dt should not exeed 50ms (20fps)
    if (dtime.asMilliseconds() > 50) {
        m_sinceLastUpdate += sf::milliseconds(50);

        Logger::warn("ApplicationTime::update")
                << "Frame time just exceeded 50ms and is set down to 50ms. Its time was (ms): "
                << std::to_string(dtime.asMilliseconds()) << "." << Logger::endl;
    } else {
        m_sinceLastUpdate += dtime;
    }
}


sf::Time ApplicationTime::realTotalTime() const {
    return m_realTotalTime;
}
