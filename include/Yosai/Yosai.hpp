//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 23.02.19.
//

#ifndef YOSAI_YOSAI_HPP
#define YOSAI_YOSAI_HPP

#include <Kigen/application/IApplication.hpp>
#include <Kigen/state/StateControl.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <Yosai/states/AllStates.hpp>

class Yosai final: public kigen::IApplication {
public:
    Yosai();

    bool is_runing() override;

    //void process_arguments(int argc, char *argv[]) {};
private:
    void update_input() override;
    void update_logic(const sf::Time &deltaTime) override;
    void update_graphics() override;
    void render() override;

    void init_state_control();
    void init_services();

private:
    StateControl m_stateControl;
    sf::RenderWindow m_renderWindow;

};


#endif //YOSAI_YOSAI_HPP
