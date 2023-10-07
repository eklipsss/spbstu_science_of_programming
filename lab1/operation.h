#include <stack>
#include <functional>
#include <string>

using realisation = std::function<void(std::stack<double>&)>;

class Operation {
private:
	std::string type;
	int priority; //[0,3] 
public:
	Operation(std::string type, int prior, realisation func) : type(type), priority(prior), func(func) {}
	Operation(Operation const& other) : type(other.type), priority(other.priority), func(other.func) {}
	~Operation() = default;

	std::string get_type() { return type; }
	int get_priority() { return priority; }
	realisation func;
};
