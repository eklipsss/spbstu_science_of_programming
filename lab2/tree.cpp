#include "tree.h"

void XMLTree::load_tree(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) 
        throw std::runtime_error("File not found\n");

    std::stack<node_shptr> node_stack;

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
            tag_name = tag_name.substr(0, pos+1);

            node_shptr new_node = std::make_shared<Node>(tag_name, tag_value);

            if (i == 0) 
                root = new_node;
            else {
                while (node_stack.size() > i) node_stack.pop();
                node_stack.top()->add(new_node);
            }

            node_stack.push(new_node);
        }
    }
}

std::string XMLTree::create_tree_str(node_shptr node, int depth) {
    std::string tree_str = "";

    for (int i = 0; i < depth; ++i) tree_str += "\t";
    tree_str += node->get_name() + " " + std::to_string(node->get_value()) + "\n";
    for (auto child : node->get_children()) tree_str += create_tree_str(child, depth + 1);
    for (int i = 0; i < depth; ++i) tree_str += "\t";
    tree_str += node->get_name().substr(0, 1) + "/" + node->get_name().substr(1) + "\n";

    return tree_str;
}

void XMLTree::save_tree(const std::string& filename) {
    std::ofstream file(filename);
    if (!file)
        throw std::runtime_error("File not found\n");
    if (!root) {
        file << "Tree is empty";
        return;
    }
    file << create_tree_str(root, 0);
}

void XMLTree::for_each(std::function<void(const Node&)> func) {
    root->for_each(func); 
}

void XMLTree::print_tree() {
    if (!root) {
        std::cout << "Tree is empty";
        return;
    }
    std::cout << create_tree_str(root, 0);
}