//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#ifndef INCLUDED_STATE_HPP
#define INCLUDED_STATE_HPP

#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

namespace sf {
    class RenderWindow;
}

class StateControl;

class State {
public:
    typedef std::unique_ptr<State> Ptr;
public:
    explicit State(StateControl &stack): m_stack(&stack) {};

    virtual ~State() = default;

    virtual void draw(sf::RenderTarget &renderTarget) = 0;

    virtual bool update(const sf::Time &deltaTime) = 0;

    virtual bool handleEvent(const sf::Event &event) = 0;

    virtual void onActivate(){};

    virtual void onDestroy(){};

protected:
    void requestStackPush(States::ID id);

    void requestStackPop();

    void requestStateClear();

private:
    StateControl *m_stack;
};

#endif //INCLUDED_STATE_HPP
