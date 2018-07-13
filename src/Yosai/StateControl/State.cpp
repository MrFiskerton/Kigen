//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#include <Yosai/StateControl/State.hpp>
#include <Yosai/StateControl/StateControl.hpp>

State::State(StateControl &stack) : m_stack(&stack) {

}

void State::onActivate() {

}

void State::onDestroy() {

}

void State::requestStackPush(state::ID stateID) {
    m_stack->pushState(stateID);
}

void State::requestStackPop() {
    m_stack->popState();
}

void State::requestStateClear() {
    m_stack->clearStates();
}