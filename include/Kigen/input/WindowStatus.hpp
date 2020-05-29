//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 21.07.18.
//

#ifndef INCLUDED_WINDOWCONTROLLER_HPP
#define INCLUDED_WINDOWCONTROLLER_HPP

#include "AbstractDevice.hpp"

namespace kigen {
namespace device {

class WindowStatus : public AbstractDevice {
public:
    void clear() override;

    void push(const sf::Event &event) override;

    bool isClosed();

    bool isResized();

    bool isGainedFocus();

    bool isLostFocus();

private:
    bool m_closed, m_resized, m_lostFocus, m_gainedFocus;
};

} //namespace device
} //namespace kigen

#endif //INCLUDED_WINDOWCONTROLLER_HPP
