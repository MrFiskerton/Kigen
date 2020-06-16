//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#ifndef INCLUDED_MENUSTATE_HPP
#define INCLUDED_MENUSTATE_HPP

#include <Kigen/state/State.hpp>

class MenuState : public State {

public:
    MenuState(StateControl &stack);
    virtual ~MenuState();

    void draw(sf::RenderTarget& target) override;
    bool update(const sf::Time& delta) override;
    bool handleEvent(const sf::Event &event) override;
private:

};


#endif //INCLUDED_MENUSTATE_HPP
