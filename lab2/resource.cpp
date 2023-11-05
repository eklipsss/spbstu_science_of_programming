#include "resource.h"
std::unique_ptr<XMLresource> XMLresource::create() {
	return std::unique_ptr<XMLresource>(new XMLresource());
}

void XMLresource::load(const std::string& filename) { 
	tree->load_tree(filename); 
}

void XMLresource::save(const std::string& filename) { 
	tree->save_tree(filename); 
}

void XMLresource::print() { 
	tree->print_tree(); 
}

Node::iterator XMLresource::begin() { 
	return tree->begin(); 
}

Node::iterator XMLresource::end() { 
	return tree->end(); 
}

Node::iterator XMLresource::find(const int& value) {
	return tree->find(value); 
}

Node::iterator XMLresource::find(const std::string& name) { 
	return tree->find(name); 
}

Node::iterator XMLresource::add(Node::iterator& iter, const std::string& name, const int& value) { 
	return tree->add(iter, name, value); 
}

bool XMLresource::erase(Node::iterator& iter) { 
	return tree->erase(iter); 
}
