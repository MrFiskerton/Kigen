//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.03.19.
//

#ifndef YOSAI_LOGICNODE_HPP
#define YOSAI_LOGICNODE_HPP

#include <utility>
#include "ActionNode.hpp"

namespace kigen {
namespace action {

class LogicNode : public ActionNode {
public:
    LogicNode(ActionNode::Ptr lhs, ActionNode::Ptr rhs) : m_left(std::move(lhs)), m_right(std::move(rhs)) {};

    bool test(const InputControl &buffer) const override = 0;

protected:
    ActionNode::Ptr m_left;
    ActionNode::Ptr m_right;
};

// Logical OR operator
class OrNode : public LogicNode {
public:
    OrNode(ActionNode::Ptr lhs, ActionNode::Ptr rhs) : LogicNode(std::move(lhs), std::move(rhs)) {};

    bool test(const InputControl &buffer) const override {
        return m_left->test(buffer) || m_right->test(buffer);
    };

    bool test() const override {
        return m_left->test() || m_right->test();
    }
};

// Logical AND operator
class AndNode : public LogicNode {
public:
    AndNode(ActionNode::Ptr lhs, ActionNode::Ptr rhs) : LogicNode(std::move(lhs), std::move(rhs)) {};

    bool test(const InputControl &buffer) const override {
        return m_left->test(buffer) && m_right->test(buffer);
    };
};

// Logical NOT operator
class NotNode : public ActionNode {
public:
    explicit NotNode(ActionNode::Ptr action) : m_action(std::move(action)) {}

    bool test(const InputControl &buffer) const override {
        return !m_action->test(buffer);
    };
private:
    ActionNode::Ptr m_action;
};

} //namespace action
} //namespace kigen

#endif //YOSAI_LOGICNODE_HPP 
