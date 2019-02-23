//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#include <Kigen/state/StateControl.hpp>

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

void StateControl::pushState(States::ID stateID) {
    m_pending_list.emplace_back(StateAction::Push, stateID);
}

void StateControl::forcePushState(States::ID stateID) {
    m_stack.push_back(createState(stateID));
}

void StateControl::popState() {
    m_pending_list.emplace_back(StateAction::Pop);
}

void StateControl::clearStates() {
    m_pending_list.emplace_back(StateAction::Clear);
}

bool StateControl::isEmpty() const {
    return m_stack.empty();
}

State::Ptr StateControl::createState(States::ID stateID) {
    auto found = m_state_factories.find(stateID);
    assertion(found != m_state_factories.end(), "State not found in states factory");
    return found->second();
}

void StateControl::applyPendingChanges() {
    for (PendingChange &change : m_pending_list) {
        switch (change.m_action) {
            case Push:
                m_stack.push_back(createState(change.m_stateId));
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