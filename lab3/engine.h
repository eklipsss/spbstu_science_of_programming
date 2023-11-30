#pragma once
#include "wrapper.h"

class Engine {
private:
	std::unordered_map<std::string, Wrapper*> commands;
	int execute_exep(const std::string& command, const std::unordered_map<std::string, int>& args) {
		if (commands.find(command) == commands.end())
			throw std::runtime_error(" (!) ERROR: Command [" + command + "] has not been registered");
		Wrapper* wrapper = commands.find(command)->second;
		return wrapper->execute(args);
	}
public:
	void register_command(Wrapper* wrapper, const std::string&  command_name) {
		if (commands.find(command_name) != commands.end()) {
			std::cout << " (!) Command [" + command_name + "] is already exist" << std::endl;
			std::cout << "  - if you want to overwrite the command - use function 'reset_command'" << std::endl;
			std::cout << "  - if you want to keep the exiting command - create a command with a new name " << std::endl;
		}
		else
			commands.insert({ command_name, wrapper });
	}
	void reset_command(Wrapper* wrapper, const std::string& command_name) {
		if (commands.find(command_name) == commands.end())
			std::cout << " (!) Command [" + command_name + "] not found - use function 'register_command'" << std::endl;
		else commands[command_name] = wrapper;
	}
	int execute(const std::string& command, const std::unordered_map<std::string, int>& args) {
		int res = 0;
		try {
			res = execute_exep(command, args);
		}
		catch (std::exception& error) {
			std::cout << error.what() << std::endl;
		}
		return res;
	}
};