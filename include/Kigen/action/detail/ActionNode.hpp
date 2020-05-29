//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.03.19.
//

#ifndef YOSAI_ACTIONNODE_HPP
#define YOSAI_ACTIONNODE_HPP

#include <memory>
#include <functional>

namespace kigen {
    class InputControl;
namespace action {

// Operation base class for event actions. The operations are organized in a tree structure.
class ActionNode {
public:
    typedef std::shared_ptr<ActionNode> Ptr;
public:
    virtual ~ActionNode() = default;

    virtual bool test() const = 0;
};

} //namespace action
} //namespace kigen

#endif //YOSAI_ACTIONNODE_HPP 
