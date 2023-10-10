#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <Windows.h>
#include <stack>
#include <list>
#include <algorithm>
#include <sstream>

#include "operation.h"

class Calculator {
private:
	std::stack<double> numbers;
	std::stack<Operation*> cur_operations;
	std::vector<Operation*> operations;
	std::vector<HINSTANCE> dlls;
	std::string expression;

public:
	Calculator();
	~Calculator();

	void base_operations();
	void load_dll();
	void import_functions(HMODULE dll);
	std::string solve();
	void put_expression();
	void delete_spaces();
	std::string check_expression() { return this->expression; }
	void math();
};