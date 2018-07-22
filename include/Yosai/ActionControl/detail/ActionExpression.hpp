//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 22.07.18.
//

#ifndef INCLUDED_ACTIONEXPRESSION_HPP
#define INCLUDED_ACTIONEXPRESSION_HPP

#include <Yosai/InputControl/InputControl.hpp>

#include <vector>
#include <functional>
#include <memory>

namespace detail {
    class EventActionNode;
    class EventBuffer {
    public:
        EventBuffer();

        // Modifiers
        void push(const sf::Event &event);
        void clear();
        void poll_events(sf::Window &window);

        // Accessors
        bool contains(const EventActionNode &event_node) const;
    private:
        // Note: Since there are at most a few dozens of events per frame (at a decent framerate not even that),
        // std::vector and linear search is fine
        std::vector<sf::Event> m_buffer;
        bool window_has_focus;
    };

//--------------------------------------BASE NODE---------------------------------------------------------------------//
    // Operation base class for event actions. The operations are organized in a tree structure.
    class ActionNode {
    public:
        typedef std::shared_ptr<ActionNode> Ptr;
    public:
        virtual ~ActionNode() = default;
        virtual bool test(const EventBuffer &buffer) const = 0;
    };
//--------------------------------------------------------------------------------------------------------------------//

//--------------------------------------EVENT BASED NODES-------------------------------------------------------------//
    // Class between ActionNode and concrete Event classes
    class EventActionNode : public ActionNode {
    public:
        EventActionNode();
        bool test(const EventBuffer &buffer) const override;
        virtual bool isEventActive(const sf::Event &event) const = 0;
    protected:
        sf::Event m_event;
    };

    // Operation node class for other SFML events
    class MiscEventLeaf : public EventActionNode {
    public:
        explicit MiscEventLeaf(sf::Event::EventType event_type);
        bool isEventActive(const sf::Event &event) const override;
    };

    // Operation node class for key events (either pressed or released)
    class KeyboardEventLeaf : public EventActionNode {
    public:
        KeyboardEventLeaf(sf::Keyboard::Key key, bool pressed);
        bool isEventActive(const sf::Event &event) const override;
    };

    // Operation node class for mouse button events (either pressed or released)
    class MouseEventLeaf : public EventActionNode {
    public:
        MouseEventLeaf(sf::Mouse::Button button, bool pressed);
        bool isEventActive(const sf::Event &event) const override;
    };

    // Operation node class for user-defined event-based actions
    class CustomEventLeaf : public EventActionNode {
    public:
        explicit CustomEventLeaf(std::function<bool(const sf::Event &)> trigger);
        bool isEventActive(const sf::Event &event) const override;
    private:
        std::function<bool(const sf::Event &)> m_trigger;
    };
//--------------------------------------------------------------------------------------------------------------------//

//---------------------------------------REALTIME BASED NODES---------------------------------------------------------//
    // Class between ActionNode and concrete Realtime classes
    class RealtimeActionNode : public ActionNode {
    public:
        bool test(const EventBuffer &buffer) const override;
        virtual bool isRealtimeActive() const = 0;
    };

    // Operation node class for keys currently held down
    class KeyboardRealtimeLeaf : public RealtimeActionNode {
    public:
        explicit KeyboardRealtimeLeaf(sf::Keyboard::Key key, bool pressed);
        bool isRealtimeActive() const override;
    private:
        sf::Keyboard::Key m_key;
        bool m_pressed;
    };

    // Operation node class for mouse buttons currently held down
    class MouseRealtimeLeaf : public RealtimeActionNode {
    public:
        explicit MouseRealtimeLeaf(sf::Mouse::Button button, bool pressed);
        bool isRealtimeActive() const override;
    private:
        sf::Mouse::Button m_button;
        bool m_pressed;
    };

    // Operation node class for user-defined realtime-based actions
    class CustomRealtimeLeaf : public RealtimeActionNode {
    public:
        explicit CustomRealtimeLeaf(std::function<bool()> trigger);
        bool isRealtimeActive() const override;
    private:
        std::function<bool()> m_trigger;
    };
//--------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------OPERATION NODES----------------------------------------------------------//
    // Logical OR operator
    class OrNode : public ActionNode {
    public:
        OrNode(ActionNode::Ptr lhs, ActionNode::Ptr rhs);
        bool test(const EventBuffer &buffer) const override;
    private:
        ActionNode::Ptr m_left;
        ActionNode::Ptr m_right;
    };

    // Logical AND operator
    class AndNode : public ActionNode {
    public:
        AndNode(ActionNode::Ptr lhs, ActionNode::Ptr rhs);
        bool test(const EventBuffer &buffer) const override;
    private:
        ActionNode::Ptr m_left;
        ActionNode::Ptr m_right;
    };

    // Logical NOT operator
    class NotNode : public ActionNode {
    public:
        explicit NotNode(ActionNode::Ptr action);
        bool test(const EventBuffer &buffer) const override;
    private:
        ActionNode::Ptr m_action;
    };
//--------------------------------------------------------------------------------------------------------------------//
} // namespace detail


#endif //INCLUDED_ACTIONEXPRESSION_HPP
