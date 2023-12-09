#pragma once
#include <functional>
#include <vector>
#include <unordered_map>

class Wrapper {
private:
    std::function<int(std::vector<int>&)> command;
    std::unordered_map<std::string, int> args;

    template<typename ClassType, typename Func, size_t... I>
    void set_command(ClassType* object, Func func, std::index_sequence<I...>) {
        command = [object, func](std::vector<int>& f_args) { return ((object->*func)(f_args[I]...)); };
    }

    bool is_exist(std::string arg_name, std::unordered_map<std::string, int> const& input_args) {
        if (input_args.find(arg_name) != input_args.end())
            return true;
        return false;
    }

public:
    template<typename ClassType, typename... Args>
    Wrapper(ClassType* object, int (ClassType::* func)(Args...), std::unordered_map<std::string, int> const& args) : args(args) {
        if (sizeof...(Args) != args.size())
            std::cout << " (!) ERROR: Incorrect wrapper - the number of arguments does not match the function arguments" << std::endl;
        else set_command(object, func, std::make_index_sequence<sizeof...(Args)>{});
    }

    int execute(std::unordered_map<std::string, int> const& input_args) {
        std::vector<int> vec_args;
        if (input_args.size() != args.size())
            throw std::runtime_error(" (!) ERROR: the number of input arguments does not match the function arguments");
        for (auto& arg : args) {
            if (!is_exist(arg.first, input_args))
                throw std::runtime_error(" (!) ERROR: input argument [" + arg.first + "] not found");
            vec_args.push_back(input_args.find(arg.first)->second);
        }
        if (command) {
            return command(vec_args);
        }
        else return 0;
    }  

};