#include "pow.h"

extern "C" __declspec(dllexport) std::string type() {
	std::string s = "^";
	return s;
}

extern "C" __declspec(dllexport) bool binary() {
	bool b = 1;
	return b;
}

extern "C" __declspec(dllexport) int priority() {
	int p = 3;
	return p;
}

extern "C" __declspec(dllexport) double operation(double x, double y) {
	double r = pow(x,y);
	return r;
}
