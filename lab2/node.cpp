#include "node.h"

void Node::for_each(std::function<void(const Node&)> func){
    func(*this);
    for (const auto& child : children)
        child->for_each(func);
}



