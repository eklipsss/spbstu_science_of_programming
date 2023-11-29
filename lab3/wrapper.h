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

public:
    template<typename ClassType, typename... Args>
    Wrapper(ClassType* object, int (ClassType::* func)(Args...), std::unordered_map<std::string, int> const& args) : args(args) {
        set_command(object, func, std::make_index_sequence<sizeof...(Args)>{});
    }
    int execute(std::unordered_map<std::string, int> const& args) {
        std::vector<int> vec_args;
        for (auto& arg : args) {
            vec_args.push_back(arg.second);
        }
        return command(vec_args);
    }    
};