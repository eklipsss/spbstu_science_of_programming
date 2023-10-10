cmake_minimum_required(VERSION 3.8)
project ("Calculator")
set(CMAKE_CXX_STANDARD 17)
add_executable (Calculator "main.cpp" "calculator.cpp" "calculator.h" "operation.h")

add_custom_target(AddPlugins ALL)

add_custom_command(
TARGET AddPlugins
COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/plugins
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/plugins ${CMAKE_BINARY_DIR}/plugins

)

add_dependencies("Calculator" AddPlugins)