#include "calculator.h"

Calculator::Calculator() //конструктор
{
	base_operations();
}

Calculator::~Calculator() //деструктор
{
	operations.clear();
}

void Calculator::base_operations()
{
	Operation* add = new Operation("+", 1, [](std::stack<double>& args) {
		if (args.size() < 2)
			std::exception("Error: There must be 2 arguments for addition\n");
		double arg1 = args.top();
		args.pop();
		std::cout << arg1 << "+" << args.top() << std::endl;
		double arg2 = args.top() + arg1;
		args.top() = arg2;
		});

	Operation* sub = new Operation("-", 1,[](std::stack<double>& args) {
		if (args.size() < 2) {
			//std::exception("Error: There must be 2 arguments for substract\n");
			std::cerr << "Меньше двух аргументов для вычитания" << std::endl;
		}
		double arg1 = args.top();
		args.pop();
		std::cout << args.top() << "-" << arg1 << std::endl;
		double arg2 = args.top() - arg1;
		args.top() = arg2;
		});

	Operation* mul = new Operation("*", 2, [](std::stack<double>& args) {
		if (args.size() < 2)
			std::exception("Error: There must be 2 arguments for multiplication\n");
		double arg1 = args.top();
		args.pop();
		std::cout << arg1 << "*" << args.top() << std::endl;
		double arg2 = args.top() * arg1;
		args.top() = arg2;

		});

	Operation* div = new Operation("/", 2, [](std::stack<double>& args) {
		if (args.size() < 2)
			std::exception("Error: There must be 2 arguments for division\n");
		if (args.top() == 0)
			std::exception("Error: The second argument cannot be 0\n");
		double arg1 = args.top();
		args.pop();
		std::cout << args.top() << "/" << arg1 << std::endl;
		double arg2 = args.top() / arg1;
		args.top() = arg2;
		});

	Operation* left_bracket = new Operation("(", 3, nullptr);
	Operation* right_bracket = new Operation(")", 3, nullptr);

	operations.push_back(add);
	operations.push_back(sub);
	operations.push_back(mul);
	operations.push_back(div);
	operations.push_back(left_bracket);
	operations.push_back(right_bracket);

}

void Calculator::put_expression() 
{
	std::cout << "Expression: " << std::endl;
	std::getline(std::cin, expression);
	for (int i = 0; i < expression.length(); i++)
	{
		if (expression[i] == ' ')
		{
			expression.erase(expression.begin() + i);
			i--;
		}
	}
}

std::string Calculator::solve()
{
	char c;
	std::string buf;
	for (int i = 0; i < expression.size(); i++) {
		c = expression[i];
		if (c >= '0' && c <= '9' || c == '-' && i == 0) { //число
			int j = i;
			bool point = false;
			while (c >= '0' && c <= '9' || c == '-' && j == 0 || c == '.') {
				//c = expression[j];
				if (c == '.') {
					if (point) {
						std::cerr << "error: a number can't have two separators (dots)";
					}
					point = true;
				}
				buf += c;
				j++;
				c = expression[j];
			}
			//std::cout << buf << std::endl;
			double num = std::stod(buf);
			numbers.push(num);
			i += buf.size() - 1;
			buf = "";
		}
		else { //не число
			//std::cout << c << std::endl;
			bool oper_exists = false;
			for (auto const& oper : operations) { // проверяем совпадение элементов строки с названиями доступных операций
				bool match = true;
				for (int k = 0; k < oper->get_type().size(); ++k) {
					if (oper->get_type()[k] != expression[i + k]) {
						match = false;
						break;
					}
				}
				if (match) { // если соответствующая операция нашлась
					oper_exists = true;
					i += oper->get_type().size() - 1;

					if (cur_operations.empty() || oper->get_type() == "(") cur_operations.push(oper);
					else if (oper->get_type() == ")") {
						math();
					}
					else {
						if (oper->get_priority() > cur_operations.top()->get_priority() || cur_operations.top()->get_type() == "(") {
							cur_operations.push(oper);
						}
						else {
							math();
							cur_operations.push(oper);
						}
					}
					break;
				}
			}
			if (!oper_exists) {
				std::cerr << "Operation or symbol is not correct\n";
				exit(1);
			}
		}

	}
	math();
	std::string str = std::to_string(numbers.top());
	return str;
}

void Calculator::math() {
	while (!cur_operations.empty()) {
		if (cur_operations.top()->get_type() == "(") {
			cur_operations.pop();
		}
		else {
			for (auto const& item : operations) {
				if (item->get_type() == cur_operations.top()->get_type()) {
					item->func(numbers);
					cur_operations.pop();
					break;
				}
			}
		}
	}
}



