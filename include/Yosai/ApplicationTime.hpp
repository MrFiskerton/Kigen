//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#ifndef INCLUDED_APPLICATIONTIME_HPP
#define INCLUDED_APPLICATIONTIME_HPP


#include <SFML/System/Time.hpp>
#include <Yosai/Util/Util.hpp>

class ApplicationTime {
public:
    ApplicationTime() = default;

    virtual ~ApplicationTime() = default;

    void update(const sf::Time &dtime);

    sf::Time realTotalTime() const;

public:
    sf::Time m_sinceLastUpdate;
private:
    sf::Time m_realTotalTime;
};

#endif //INCLUDED_APPLICATIONTIME_HPP
