//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 21.07.18.
//

#ifndef INCLUDED_WINDOWCONTROLLER_HPP
#define INCLUDED_WINDOWCONTROLLER_HPP

#include "AbstractDevice.hpp"

class WindowController : public AbstractDevice {
public:
    WindowController();

    virtual ~WindowController();

    void clear_events() override;

    void handle_event(const sf::Event &event) override;

    bool isClosed();
    bool isResized();
    bool isGainedFocus();
    bool isLostFocus();

private:
    bool m_closed, m_resized, m_lostFocus, m_gainedFocus;
};


#endif //INCLUDED_WINDOWCONTROLLER_HPP
