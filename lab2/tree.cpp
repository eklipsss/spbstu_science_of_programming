#include "tree.h"

void XMLtree::load_tree(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File not found" << std::endl;
        return;
    }

    std::stack<node_shptr> node_stack;
    node_wptr parent;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) 
            continue;

        size_t i = 0;
        while (line[i] == '\t')  ++i;

        std::string tag_name = line.substr(i);
        if (!tag_name.find("</"))
            continue;
        else {
            size_t pos = tag_name.find('>');
            std::string tag_value_str = tag_name.substr(pos + 2);
            
            int tag_value = std::stoi(tag_value_str);
            tag_name = tag_name.substr(1, pos-1);

            if (i == 0) {
                node_shptr new_node = std::make_shared<Node>(tag_name, tag_value);
                root = new_node;
                node_stack.push(root);
            }
            else {
                while (node_stack.size() > i) node_stack.pop();
                node_shptr new_node = std::make_shared<Node>(tag_name, tag_value, node_stack.top());
                node_stack.top()->add_child(new_node);
                node_stack.push(new_node);
            }
        }
    }
}

std::string XMLtree::create_tree_str(node_shptr node, int depth) const {
    std::string tree_str = "";

    for (int i = 0; i < depth; ++i) tree_str += "\t";
    tree_str += "<" + node->get_name() + "> " + std::to_string(node->get_value()) + "\n";
    for (auto child : node->get_children()) tree_str += create_tree_str(child, depth + 1);
    for (int i = 0; i < depth; ++i) tree_str += "\t";
    tree_str += "</" + node->get_name() + ">\n";

    return tree_str;
}

void XMLtree::save_tree(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "File not found" << std::endl;
        return;
    }
    if (!root) 
        file << "Tree is empty";
    else 
        file << create_tree_str(root, 0);
}

void XMLtree::for_each(std::function<void(const Node&)> func) {
    root->for_each(func); 
}

void XMLtree::print_tree() const {
    std::cout << "----------\nXML tree:\n----------\n";
    if (!root) {
        std::cout << "Tree is empty";
        return;
    }   
    std::cout << create_tree_str(root, 0);
}

Node::iterator XMLtree::add(Node::iterator& iter, const std::string& name, const int& value) {
    return iter.add(name, value, iter.get_node());
}

Node::iterator XMLtree::find(const int& value){
    for (Node::iterator i = this->begin(); i != this->end(); ++i)
        if (i->get_value() == value)
            return i;

    std::cerr << "Node with this value not found!" << std::endl;
    Node::iterator iter = Node::iterator(nullptr, nullptr);
    return iter;
}

Node::iterator XMLtree::find(const std::string& name) {
    for (Node::iterator i = this->begin(); i != this->end(); ++i) 
        if (i->get_name() == name)
            return i;
    
    std::cerr << "Node with this tag name not found!" << std::endl;
    Node::iterator iter = Node::iterator(nullptr, nullptr);
    return iter;
}

bool XMLtree::erase(Node::iterator& iter) {
    if (iter.get_node() == nullptr || iter.get_root() == nullptr){
        std::cerr << "Operation canceled" << std::endl;
        return false;
    }
    else if (*iter.get_node() == *iter.get_root()) {
            root = nullptr;
    }
    else iter.erase();
    return true;
}