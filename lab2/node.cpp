#include "node.h"

void Node::for_each(std::function<void(const Node&)> func){
    func(*this);
    for (const auto& child : children)
        child->for_each(func);
}

void Node::delete_node() {
    if (parent.lock()) {
        for (int i = 0; i < children.size(); i++) {
            children[i]->parent = parent;
            parent.lock()->add_child(children[i]);
        }
        delete_from_children();
    }
    else {
        std::cerr << "Operation canceled" << std::endl;
        return;
    }
}

void Node::delete_from_children() {
    std::vector<node_shptr>& buf = parent.lock()->children;
    for (int i = 0; i < buf.size(); i++) {
        buf[i].reset();
        buf.erase(buf.begin() + i);
        break;
    }
}

int Node::child_number(Node* node) const{
    for (int i = 0; i < children.size(); i++) {
        if (children[i].get() == node && i != children.size())
            return i;
        else return -1;
    }
}

Node::node_shptr Node::next_node(){
    if (parent.lock()) { 
        std::vector<node_shptr> buf_children = parent.lock()->get_children();
        int i = parent.lock()->child_number(this);
        if (i != -1)
            return buf_children[i + 1];
        else return parent.lock();
    }
    else return nullptr;
}

void Node::print_node() const{
    std::cout << "[ name: " << name << " | value: " << value << " ]" << std::endl;
}

bool Node::operator ==(const Node& other) {
    if (name == other.get_name() && value == other.get_value())
        return true;
    else
        return false;
}

bool Node::operator !=(const Node& other) {
    if (name != other.get_name() || value != other.get_value())
        return true;
    else
        return false;
}

void Node::iterator::next(){
    node_shptr buf = node->next_node();
    if (buf)
        node = buf;
    else 
        node = nullptr;
}

Node::iterator& Node::iterator::operator ++ () {
    next();
    return *this;
}


bool Node::iterator::operator == (const iterator& other) const {
    if (node && other.node)
        return (*node == *other.node && *root == *other.root);
    else
        return (node == other.node);
}
bool Node::iterator::operator != (const iterator& other) const { 
    if (node && other.node)
        return (*node != *other.node || *root != *other.root);
    else
        return (node != other.node);
}

Node::iterator Node::iterator::add(const std::string& name, const int& value, node_shptr parent) {
    if (node) {
        std::shared_ptr<Node> new_node = std::make_shared<Node>(name, value, parent);
        node->add_child(new_node);
        Node::iterator new_iter(new_node, root);
        return new_iter;
    }
    std::cerr << "Operation canceled" << std::endl;
    return *this;
}

void Node::iterator::erase() {
    node->delete_node();
}

Node::iterator Node::begin() {
    iterator iter = iterator(std::make_shared<Node>(name, value), std::make_shared<Node>(name, value));
    if (this->children.size() != 0) {
        node_shptr node = this->children[0];
        for (int i = 0; node->children.size(); i++)
            node = node->children[0];
        iter = iterator(node, std::make_shared<Node>(name, value));
    }
    return iter;
}

Node::iterator Node::end() {
    iterator iter = iterator(nullptr, std::make_shared<Node>(name, value));
    return iter;
}


