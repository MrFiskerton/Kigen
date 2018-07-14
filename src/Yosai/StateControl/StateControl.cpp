//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#include "Yosai/StateControl/StateControl.hpp"


StateControl::StateControl() : m_stack(), m_pending_list(), m_state_factories() {

}

void StateControl::update(const sf::Time &deltaTime) {
    // Iterate from top to bottom, stop as soon as frame_time() returns false
    for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr) {
        if (!(*itr)->update(deltaTime)) {
            break;
        }
    }
    applyPendingChanges();
}

void StateControl::draw(sf::RenderTarget &renderTarget) {
    // Draw all active states from bottom to top
    for (State::Ptr &state : m_stack) {
        state->draw(renderTarget);
    }
}

void StateControl::handleEvent(const sf::Event &event) {
    // Iterate from top to bottom, stop as soon as handleEvent() returns false
    for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr) {
        if (!(*itr)->handleEvent(event)) {
            break;
        }
    }
    applyPendingChanges();
}

void StateControl::pushState(state::ID stateID) {
    m_pending_list.emplace_back(Action::Push, stateID);
}

void StateControl::forcePushState(state::ID stateID) {
    m_stack.push_back(createState(stateID));
}

void StateControl::popState() {
    m_pending_list.emplace_back(Action::Pop);
}

void StateControl::clearStates() {
    m_pending_list.emplace_back(Action::Clear);
}

bool StateControl::isEmpty() const {
    return m_stack.empty();
}

State::Ptr StateControl::createState(state::ID stateID) {
    auto found = m_state_factories.find(stateID);
    assertion(found != m_state_factories.end(), "State not found in state factory");
    return found->second();
}

void StateControl::applyPendingChanges() {
    for (PendingChange &change : m_pending_list) {
        switch (change.action) {
            case Push:
                m_stack.push_back(createState(change.id));
                break;
            case Pop:
                m_stack.back()->onDestroy();
                m_stack.pop_back();
                if (!m_stack.empty()) {
                    m_stack.back()->onActivate();
                }
                break;
            case Clear:
                for (State::Ptr &state : m_stack) {
                    state->onDestroy();
                }
                m_stack.clear();
                break;
        }
    }
    m_pending_list.clear();
}

StateControl::PendingChange::PendingChange(StateControl::Action action, state::ID stateID) : action(action),
                                                                                             id(stateID) {}