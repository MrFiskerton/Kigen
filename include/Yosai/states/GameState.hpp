//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 28.05.2020.
//

#ifndef YOSAI_GAMESTATE_HPP
#define YOSAI_GAMESTATE_HPP

#include <Kigen/state/State.hpp>

class GameState : public State {

public:
    explicit GameState(StateControl &stack);
    ~GameState() override;

    void draw(sf::RenderTarget& renderTarget) override;
    bool update(const sf::Time& deltaTime) override;
    bool handleEvent(const sf::Event &event) override;

};


#endif //YOSAI_GAMESTATE_HPP
