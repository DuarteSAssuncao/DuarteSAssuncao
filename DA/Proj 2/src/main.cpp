/**
 * @file main.cpp
 * @author G17_5
 * @brief Main file for compilation. Initializes the project
 * @date 17/04/2024
 */

#include <iostream>
#include <cstring>

#include "../lib/Graph.hpp"
#include "../lib/Macros.hpp"
#include "../lib/Parser.hpp"
#include "../lib/Runtime.hpp"

int main(int argc, char *argv[]) {
    Runtime runtime;

    if (argc > 1) {
        std::vector<std::string> command = {"load", argv[1]};
        if (argc > 2) command.emplace_back(argv[2]);
        runtime.load(command);
    }

    runtime.run();
    return 0;
}
