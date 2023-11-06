cmake_minimum_required(VERSION 3.8)
project ("XMLresource")
set(CMAKE_CXX_STANDARD 17)

add_executable (XMLresource "main.cpp" "node.cpp" "node.h" "tree.cpp" "tree.h" "resource.cpp" "resource.h")

configure_file(xml_tree.txt xml_tree.txt)
configure_file(output.txt output.txt)