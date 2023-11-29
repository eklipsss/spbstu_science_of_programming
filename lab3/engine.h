#pragma once
#include "wrapper.h"

class Engine {
private:
	std::unordered_map<std::string, Wrapper*> commands;
public:
	void register_command(Wrapper* wrapper, const std::string&  command_name) {
		commands.insert({ command_name, wrapper });
	}
	int execute(const std::string& command, const std::unordered_map<std::string, int>& args) {
		Wrapper* wrapper = commands.find(command)->second;
		return wrapper->execute(args);
	}
};