#include <iostream>
#include <conio.h>
#include "wrapper.h"
#include "engine.h"

class Subject {
public:
    int f1(int a, int b) {
        return a - b;
    };
	int f1_new(int a, int b) {
		return a * b;
	};
	int f2(int a, int b, int c) {
		return a + b + c;
	};
};

int main() {
	Subject subj;
	Engine engine;
	std::cout << "f1(a,b) = a - b " << std::endl;
	std::cout << "f1_new(a,b) = a * b " << std::endl;
	std::cout << "f2(a,b,c) = a + b + c " << std::endl << std::endl;

	std::cout << "------------------------"  << std::endl;
	std::cout << "Correct wrapper: " << std::endl;
	std::cout << "------------------------" << std::endl;
	
	Wrapper wrapper1(&subj, &Subject::f1, { {"arg1", 0}, {"arg2", 0} });
	Wrapper wrapper1_new(&subj, &Subject::f1_new, { {"arg1", 0}, {"arg2", 0}});

	engine.register_command(&wrapper1, "command1");

	std::cout << "  f1(4,5): " << engine.execute("command1", { {"arg1", 4}, {"arg2", 5} }) << std::endl;

	std::cout << "\nNumber of arguments mismatch: " << std::endl;
	std::cout << "  f1(4,5,6): " << engine.execute("command1", { {"arg1", 4}, {"arg2", 5}, {"arg3", 6} }) << std::endl;

	std::cout << "\nRandom order of arguments: " << std::endl;
	std::cout << "  f1(5,4): " << engine.execute("command1", { {"arg2", 4}, {"arg1", 5} }) << std::endl;

	std::cout << "\nUndefined argument name: " << std::endl;
	std::cout << "  f1(4,-): " << engine.execute("command1", { {"arg1", 4}, {"argument2", 5} }) << std::endl;

	std::cout << "\nTrying to execute a non-existent command: " << std::endl;
	std::cout << "  f3(4,5): " << engine.execute("command3", { {"arg1", 4}, {"arg2", 5} }) << std::endl;

	std::cout << "\nTrying to register a new command with an existing name: " << std::endl;
	engine.register_command(&wrapper1_new, "command1");

	std::cout << "\nReset command: " << std::endl;
	engine.reset_command(&wrapper1_new, "command1");
	std::cout << "  f1_new(4,5): " << engine.execute("command1", { {"arg1", 4}, {"arg2", 5} }) << std::endl;

	std::cout << "\nReset command with undefined name: " << std::endl;
	engine.reset_command(&wrapper1, "command_1");


	std::cout << std::endl;

	std::cout << "------------------------" << std::endl;
	std::cout << "Incorrect wrapper [1]: " << std::endl;
	std::cout << "------------------------" << std::endl;
	Wrapper wrapper2(&subj, &Subject::f2, { {"arg1", 0}, {"arg2", 0}, {"arg3", 0}, {"arg4", 0} });

	engine.register_command(&wrapper2, "command2");

	std::cout << "f2: " << engine.execute("command2", { {"arg1", 4}, {"arg2", 5}, {"arg3", 6}, {"arg4", 7} }) << std::endl;

	//std::cout << "------------------------" << std::endl;
	//std::cout << "Incorrect wrapper [2]: " << std::endl;
	//std::cout << "------------------------" << std::endl;
	//Wrapper wrapper3(&subj, &Subject::f2, { {"arg1", 0}, {"arg2", 0} });

	//engine.register_command(&wrapper3, "command3");

	//std::cout << "f3: " << engine.execute("command3", { {"arg1", 4}, {"arg2", 5} }) << std::endl;

	char c;
	std::cout << "\nPress ENTER to exit " << std::endl;
	c = _getch();
	if (c == 13) {
		std::cout << "\nexit!" << std::endl;
		exit(0);
	}
	system("pause");

	return 0;
};