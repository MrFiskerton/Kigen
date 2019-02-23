//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 22.07.18.
//

#include <Kigen/action/detail/ActionExpression.hpp>

namespace detail {
    EventBuffer::EventBuffer() : m_buffer() {}

    void EventBuffer::push(const sf::Event &event) {
        m_buffer.push_back(event);
    }

    void EventBuffer::clear() {
        m_buffer.clear();
    }

    bool EventBuffer::contains(const EventActionNode &event_node) const {
        for (auto &event: m_buffer) if (event_node.isEventActive(event)) return true;
        return false;
    }

    void EventBuffer::poll_events(sf::Window &window) {
        static sf::Event event;
        while (window.pollEvent(event))
            push(event);
    }
//--------------------------------------------------------------------------------------------------------------------//


//--------------------------------------EVENT BASED NODES-------------------------------------------------------------//
    EventActionNode::EventActionNode() : ActionNode(), m_event() {}

    bool EventActionNode::test(const EventBuffer &buffer) const {
        return buffer.contains(*this);
    }

    MiscEventLeaf::MiscEventLeaf(sf::Event::EventType event_type) : EventActionNode() {
        m_event.type = event_type;
    }

    bool MiscEventLeaf::isEventActive(const sf::Event &event) const {
        return m_event.type == event.type;
    }

    KeyboardEventLeaf::KeyboardEventLeaf(sf::Keyboard::Key key, bool pressed) : EventActionNode() {
        m_event.type = pressed ? sf::Event::KeyPressed : sf::Event::KeyReleased;
        m_event.key.code = key;
    }

    bool KeyboardEventLeaf::isEventActive(const sf::Event &event) const {
        return event.type == m_event.type && event.key.code == m_event.key.code;
    }

    MouseEventLeaf::MouseEventLeaf(sf::Mouse::Button button, bool pressed) : EventActionNode() {
        m_event.type = pressed ? sf::Event::MouseButtonPressed : sf::Event::MouseButtonReleased;
        m_event.mouseButton.button = button;
    }

    bool MouseEventLeaf::isEventActive(const sf::Event &event) const {
        return event.type == m_event.type && event.mouseButton.button == m_event.mouseButton.button;
    }

    CustomEventLeaf::CustomEventLeaf(std::function<bool(const sf::Event &)> trigger)
            : EventActionNode(), m_trigger(std::move(trigger)) {}

    bool CustomEventLeaf::isEventActive(const sf::Event &event) const {
        return m_trigger(event);
    }
//--------------------------------------------------------------------------------------------------------------------//


//---------------------------------------REALTIME BASED NODES---------------------------------------------------------//
    bool RealtimeActionNode::test(const EventBuffer &buffer) const {
        return isRealtimeActive();
    }

    KeyboardRealtimeLeaf::KeyboardRealtimeLeaf(sf::Keyboard::Key key, bool pressed)
            : RealtimeActionNode(), m_key(key), m_pressed(pressed) {}

    bool KeyboardRealtimeLeaf::isRealtimeActive() const {
        return sf::Keyboard::isKeyPressed(m_key) == m_pressed;
    }

    MouseRealtimeLeaf::MouseRealtimeLeaf(sf::Mouse::Button button, bool pressed)
            : RealtimeActionNode(), m_button(button), m_pressed(pressed) {}

    bool MouseRealtimeLeaf::isRealtimeActive() const {
        return sf::Mouse::isButtonPressed(m_button) == m_pressed;
    }

    CustomRealtimeLeaf::CustomRealtimeLeaf(std::function<bool()> trigger)
            : RealtimeActionNode(), m_trigger(std::move(trigger)) {}

    bool CustomRealtimeLeaf::isRealtimeActive() const {
        return m_trigger();
    }
//--------------------------------------------------------------------------------------------------------------------//


//-------------------------------------------OPERATION NODES----------------------------------------------------------//
    OrNode::OrNode(ActionNode::Ptr lhs, ActionNode::Ptr rhs) : ActionNode(), m_left(std::move(lhs)),
                                                               m_right(std::move(rhs)) {}

    bool OrNode::test(const EventBuffer &buffer) const {
        return m_left->test(buffer) || m_right->test(buffer);
    }


    AndNode::AndNode(ActionNode::Ptr lhs, ActionNode::Ptr rhs) : ActionNode(), m_left(std::move(lhs)),
                                                                 m_right(std::move(rhs)) {}

    bool AndNode::test(const EventBuffer &buffer) const {
        return m_left->test(buffer) && m_right->test(buffer);
    }

    NotNode::NotNode(ActionNode::Ptr action) : ActionNode(), m_action(std::move(action)) {}

    bool NotNode::test(const EventBuffer &buffer) const {
        return !m_action->test(buffer);
    }
//--------------------------------------------------------------------------------------------------------------------//
}