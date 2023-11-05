#include "tree.h"

int main() {
    std::string input_file = "xml_tree.txt";
    std::string output_file = "output.txt";
    XMLtree* tree = new XMLtree();
    tree->load_tree(input_file);
    tree->print_tree();
    tree->save_tree(output_file);
	std::cout << "\n" << std::endl;

	std::cout << "From begin to end:" << std::endl;
	for (auto it = tree->begin(), end = tree->end(); it != end; ++it)
		it->print_node();
	std::cout << std::endl;

	std::cout << "\nFind: value = 4  --->  ";
	auto node_by_val = tree->find(4);
	if (node_by_val.get_node())
		node_by_val->print_node();

	std::cout << "\nFind: value = 88  --->  ";
	node_by_val = tree->find(88);
	if (node_by_val.get_node())
		node_by_val->print_node();

	std::cout << "\nFind: name = tag2  --->  ";
	auto node_by_name = tree->find("tag2");
	if (node_by_name.get_node())
		node_by_name->print_node();

	std::cout << "\nFind: name = <tag2>  --->  ";
	node_by_name = tree->find("<tag2>");
	if (node_by_name.get_node())
		node_by_name->print_node();
	std::cout << std::endl;

	std::cout << "\nAdd new node (child) [ name: new_tag | value: 6 ] to node with value = 3:" << std::endl;
	auto parent = tree->find(3);
	auto new_node = tree->add(parent, "new_tag", 6);
	tree->print_tree();
	std::cout << std::endl;

	std::cout << "\nErase new node: " << std::endl;
	if (tree->erase(new_node))
		tree->print_tree();
	std::cout << std::endl;

	std::cout << "\nErase node with value = 2: " << std::endl;
	node_by_name = tree->find(2);
	if (node_by_name.get_node())
		tree->erase(node_by_name);
	tree->print_tree();
	std::cout << std::endl;

	std::cout << "\nErase root: " << std::endl;
	node_by_name = tree->find(1);
	if (node_by_name.get_node())
		tree->erase(node_by_name);
	tree->print_tree();
	std::cout << std::endl;

    return 0;
}