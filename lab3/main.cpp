#include <iostream>
#include "wrapper.h"
#include "engine.h"

class Subject {
public:
    int f1(int a, int b) {
        return a + b;
    };
	int f2(int a, int b, int c) {
		return a + b + c;
	};
};

int main() {
	Subject subj;

	Wrapper wrapper1(&subj, &Subject::f1, {{"arg1", 0}, {"arg2", 0}});
	Wrapper wrapper2(&subj, &Subject::f2, { {"arg1", 0}, {"arg2", 0}, {"arg3", 0} });


	Engine engine;

	engine.register_command(&wrapper1, "command1");
	engine.register_command(&wrapper2, "command2");


	std::cout << "f1: " << engine.execute("command1", {{"arg1", 4}, {"arg2", 5}}) << std::endl;
	std::cout << "f2: " << engine.execute("command2", { {"arg1", 4}, {"arg2", 5}, {"arg3", 6} }) << std::endl;


	return 0;
};