#pragma once

#include "node.h"

class XMLTree {
private:
	using node_shptr = std::shared_ptr<Node>;

	node_shptr root;
	std::string create_tree_str(node_shptr node, int depth);

public:
	void load_tree(const std::string& filename);
	void save_tree(const std::string& filename);
	void for_each(std::function<void(const Node&)> func);
	void print_tree();
};
