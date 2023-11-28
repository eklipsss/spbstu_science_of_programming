#pragma once
#include "tree.h"

class XMLresource {
private:
	std::unique_ptr<XMLtree> tree;
	XMLresource() : tree(std::make_unique<XMLtree>()) {};
public:
	static std::unique_ptr<XMLresource> create();

	void load(const std::string& filename);
	void save(const std::string& filename);
	void print();

	Node::iterator begin();
	Node::iterator end();

	Node::iterator find(const int& value);
	Node::iterator find(const std::string& name);
	Node::iterator add(Node::iterator& iter, const std::string& name, const int& value);
	bool erase(Node::iterator& iter);

	~XMLresource() = default;

	XMLresource(const XMLresource&) = delete;
	XMLresource(XMLresource&&) = delete;
	XMLresource& operator = (const XMLresource&) = delete;
	XMLresource& operator = (XMLresource&&) = delete;
};