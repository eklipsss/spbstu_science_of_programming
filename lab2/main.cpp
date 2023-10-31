#include "tree.h"

int main() {
    std::string input_file = "xml_tree.txt";
    std::string output_file = "output.txt";
    XMLTree* tree = new XMLTree();
    try {
        tree->load_tree(input_file);
        tree->print_tree();
        tree->save_tree(output_file);
    }
    catch(std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    return 0;
}