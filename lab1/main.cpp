#include "calculator.h"

int main()
{
	std::cout << "Console calculator\n";
	Calculator calc;
	calc.put_expression();
	while (calc.check_expression() != "" || calc.check_expression() != "stop")
	{
		if (calc.check_expression() == "" || calc.check_expression() == "stop") break;
		std::cout << calc.check_expression() << "=" << calc.solve() << std::endl;
		calc.put_expression();
	}
	return 0;
}