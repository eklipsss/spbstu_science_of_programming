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
    using node_wptr = std::weak_ptr<Node>;

    std::string name;
    int value;
    std::vector<node_shptr> children;
    node_wptr parent;

public:
    
    Node(const std::string& name, const int& value) : name(name), value(value) {};
    Node(const std::string& name, const int& value, const node_wptr& parent) : name(name), value(value), parent(parent) {};

    
    std::string get_name() const { return name; };
    int get_value() const { return value; };
    std::vector<node_shptr> get_children() const { return children; };

    void add_child(node_shptr new_node) { children.push_back(std::move(new_node)); };
    void for_each(std::function<void(const Node&)> func);
    void delete_node();
    void delete_from_children();

    int child_number(Node* child) const;
    node_shptr next_node();

    void print_node() const;

    bool operator ==(const Node& other);
    bool operator !=(const Node& other);

    class iterator {
    private:
        node_shptr node;
        node_shptr root;

        void next(); 

    public:

        explicit iterator(node_shptr node, node_shptr root) :node(node), root(root) {};

        node_shptr get_node() { return node; };
        node_shptr get_root() { return root; };

        iterator& operator ++ ();
        iterator operator ++ (int) { return ++(*this); };
        bool operator == (const iterator& other) const;
        bool operator != (const iterator& other) const;
        Node& operator * () const { return *node; };
        Node* operator -> () const { return node.get(); };

        iterator add(const std::string& name, const int& value, node_shptr parent);
        void erase();

    };

    iterator begin();
    iterator end();
};