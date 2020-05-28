//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 23.02.19.
//

#ifndef YOSAI_YOSAI_HPP
#define YOSAI_YOSAI_HPP

#include <Yosai/states/States.hpp>
#include <Kigen/application/BasicApplication.hpp>

class Yosai final: public kigen::BasicApplication {
public:
    Yosai ();
private:
    void init_state_control() override;
    void init_actions();
    void init_services();

protected:
    void update_logic(const sf::Time &delta) override;

private:
    kigen::ActionControl<Actions::ID> m_actions;
};


#endif //YOSAI_YOSAI_HPP
