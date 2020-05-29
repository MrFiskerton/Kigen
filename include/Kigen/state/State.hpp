//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#ifndef INCLUDED_STATE_HPP
#define INCLUDED_STATE_HPP

#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <Yosai/id/StateIdentifiers.hpp>
#include <Yosai/id/ActionsIdentifiers.hpp>
#include <Yosai/id/ResourceIdentifiers.hpp>
#include <Kigen/utils/locator/Locator.hpp>
#include <Kigen/action/ActionControl.hpp>

namespace sf {
    class RenderWindow;
}

class StateControl;

class State {
public:
    typedef std::unique_ptr<State> Ptr;
public:
    explicit State(StateControl &stack);

    virtual ~State() = default;

    virtual void draw(sf::RenderTarget &target) = 0;

    virtual bool update(const sf::Time &delta) = 0;

    virtual bool handleEvent(const sf::Event &event) = 0;

    virtual void onActivate();

    virtual void onDestroy();

protected:
    void requestStackPush(States::ID id);

    void requestStackPop();

    void requestStateClear();

private:
    StateControl *m_stack;
};

#endif //INCLUDED_STATE_HPP
