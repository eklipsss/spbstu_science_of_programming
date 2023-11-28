#pragma once

#include "node.h"

class XMLtree {
private:
	using node_shptr = std::shared_ptr<Node>;
	using node_wptr = std::weak_ptr<Node>;

	node_shptr root;
	std::string create_tree_str(node_shptr node, int depth) const;

public:
	void load_tree(const std::string& filename);
	void save_tree(const std::string& filename);
	void for_each(std::function<void(const Node&)> func);
	void print_tree() const;

	Node::iterator begin();
	Node::iterator end();
	Node::iterator add(Node::iterator& iter, const std::string& name, const int& value);
	Node::iterator find(const int& value);
	Node::iterator find(const std::string& name);
	bool erase(Node::iterator& iter);
};
