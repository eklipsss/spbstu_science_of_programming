#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <functional>
#include <memory>

class Node{
private:
    using node_shptr = std::shared_ptr<Node>;

    std::string name;
    int value;
    std::vector<node_shptr> children;

public:
    
    Node(const std::string& name, const int& value) : name(name), value(value) {};
    //Node(const std::string& name, const int& value, const std::vector<node_shptr>& children) : name(name), value(value), children(children) {};

    
    std::string get_name() const { return name; };
    int get_value() const { return value; };
    std::vector<node_shptr> get_children() const { return children; };

    void add(node_shptr new_node) { children.push_back(new_node); };
    void for_each(std::function<void(const Node&)> func);
};