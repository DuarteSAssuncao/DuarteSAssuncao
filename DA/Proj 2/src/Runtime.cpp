/**
 * @file Runtime.cpp
 * @brief Definition of functions used to run the program
 * @author G17_5
 * @date 06/04/2024
 */

#include "../lib/Runtime.hpp"
#include "../lib/Parser.hpp"
#include <algorithm>
#include <iomanip>

Runtime::Runtime() : network(new Graph()) {}

void Runtime::run() {
    std::cout << ANSI_RESET << std::endl << "Welcome to our project!" << std::endl;
    std::cout << "Please, read the " << GREEN << "README.md" << ANSI_RESET << " file to know how to properly use the program." << std::endl;
    while (true) {
        std::cout << std::endl;
        help();
        std::cout << std::endl;
        if (std::cin.eof()) break; // CTRL-D
        std::cout << "> ";
        std::vector<std::string> command = readCommand();
        if (command.empty()) continue;

        begin = std::chrono::steady_clock::now();

        if (command[0] == "7" || command[0] == "exit" || command[0] == "quit") break;
        else if (command[0] == "0" || command[0] == "load") load(command);
        else if (command[0] == "1" || command[0] == "backtrack") backtrack(command);
        else if (command[0] == "2" || command[0] == "tineq") tineq(command);
        else if (command[0] == "3" || command[0] == "near") near(command);
        else if (command[0] == "4" || command[0] == "bhk") bhk(command);
        else if (command[0] == "5" || command[0] == "bhks") bhks(command);
        else if (command[0] == "6" || command[0] == "rwtsp") realWorld(command);
        else
            std::cout << RED << "Error: " << ANSI_RESET << "No such command. Type " << GREEN << "help" << ANSI_RESET
                      << " to learn the available commands.\n";

        long int milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        char fill = std::cout.fill();
        std::cout << "Command took " << milliseconds / 1000 << "." << std::setfill('0') << std::setw(3)
                  << milliseconds % 1000 << "s\n";
        std::cout.fill(fill);
    }
    std::cout << RED << "Terminating program...\n" << ANSI_RESET << "Hope to see you soon!\n";
}

static void print_path(const std::vector<Vertex *> &path) {
    if (path.empty()) {
        std::cout << YELLOW << "There is no path.\n" << ANSI_RESET;
        return;
    }

    std::cout << path[0]->getId();

    for (auto itr = path.begin() + 1; itr != path.end(); ++itr)
        std::cout << " -> " << (*itr)->getId();
}

static unsigned getSrc(const std::vector<std::string> &args) {
    if (args.size() != 2) {
        std::cout << RED << "Error: expected 1 argument (node id)." << ANSI_RESET << std::endl;
        return -1;
    }
    try {
        return std::stoul(args[1]);
    } catch (std::invalid_argument &e) {
        std::cout << RED << "Error: expected a number (node id) as the 1st argument." << ANSI_RESET << std::endl;
        return -1;
    }
}

std::vector<std::string> Runtime::readCommand() {
    std::vector<std::string> ret;

    std::string command = "";
    getline(std::cin, command);

    std::istringstream iss = std::istringstream(command);
    std::string arg = "";
    while (getline(iss, arg, ' ')) {
        ret.push_back(arg);
        arg.clear();
    }

    return ret;
}

void Runtime::help() {
    std::cout << "List of available algorithms: \n"
              << " 0 - load <edges_csv> [<nodes_csv>] : Loads the graph using the given filenames\n"
              << " 1 - backtrack                      : Solves the TSP using the Backtracking algorithm\n"
              << " 2 - tineq                          : Solves the TSP using the 2-approximation Triangle Inequality algorithm\n"
              << " 3 - near                           : Solves the TSP using the Nearest Neighbour algorithm\n"
              << " 4 - bhk                            : Solves the TSP using the Bellman-Held-Karp algorithm\n"
              << " 5 - bhks                           : Solves the TSP using the Bellman-Held-Karp String Version algorithm (slower but uses less memory)\n"
              << " 6 - rwtsp [<src_id>]               : Solves the TSP using the Real World adaptation of the 2-approximation Triangular Inequality algorithm\n"
              << " 7 - exit | quit                    : Quits the program\n"
              << "Notes:\n"
              << "    - src_id is an optional argument to choose the node to start at\n"
              << "    - You can either type the algorithm name (as shown above) or its correspondent number\n";
}

void Runtime::load(std::vector<std::string> &args) {
    switch (args.size()) {
        case 2:
            std::cout << "Deleting current graph...\n";
            delete network;
            network = new Graph();
            std::cout << "Loading graph...\n";
            parse(*network, args[1]);
            break;
        case 3:
            std::cout << "Deleting current graph...\n";
            delete network;
            network = new Graph();
            std::cout << "Loading graph...\n";
            parse(*network, args[1], args[2]);
            break;
        default:
            std::cout << RED << "Error: expected 1 or 2 arguments: load <edges_file> [<nodes_file>]" << ANSI_RESET
                      << std::endl;
            break;
    }
    end = std::chrono::steady_clock::now();
}

void Runtime::backtrack(std::vector<std::string> &args) {
    if (args.size() != 1) {
        std::cout << RED << "Error: expected no arguments." << ANSI_RESET << std::endl;
        return;
    }

    std::vector<Vertex *> result;
    std::cout << "Calculating result...\n";
    double distance = network->backtrack(0, result);

    if((result.size() != network->getVertexSet().size() + 1) || (distance < 0)) {
        std::cout << YELLOW << "There is no path.\n" << ANSI_RESET;
        end = std::chrono::steady_clock::now();
        return;
    }

    end = std::chrono::steady_clock::now();

    std::cout << "Do you want to print the path? [y/N]" << std::endl;
    std::string answer;
    getline(std::cin, answer);
    if (answer == "y") print_path(result);
    std::cout << "\nDistance: " << distance << std::endl;
}

void Runtime::tineq(std::vector<std::string> &args) {
    if (args.size() != 1) {
        std::cout << RED << "Error: expected no arguments." << ANSI_RESET << std::endl;
        return;
    }

    //network->ensureFullyConnected(true);

    std::vector<Vertex *> result;
    std::cout << "Calculating result..\n";
    double distance = network->triangleInequality(0, result);

    if((result.size() != network->getVertexSet().size() + 1) || (distance < 0)) {
        std::cout << YELLOW << "There is no path.\n" << ANSI_RESET;
        end = std::chrono::steady_clock::now();
        return;
    }

    end = std::chrono::steady_clock::now();

    std::cout << "Do you want to print the path? [y/N]" << std::endl;
    std::string answer;
    getline(std::cin, answer);
    if (answer == "y") print_path(result);
    std::cout << "\nDistance: " << distance << std::endl;
}

void Runtime::bhk(std::vector<std::string> &args) {
    if (args.size() != 1) {
        std::cout << RED << "Error: expected no arguments." << ANSI_RESET << std::endl;
        return;
    }

    std::vector<Vertex *> result;
    std::cout << "Calculating result...\n";
    double distance = network->bellmanHeldKarp(0);

    if(distance < 0) {
        std::cout << YELLOW << "There is no path.\n" << ANSI_RESET;
        end = std::chrono::steady_clock::now();
        return;
    }

    end = std::chrono::steady_clock::now();

    std::cout << "\nDistance: " << distance << std::endl;
}

void Runtime::bhks(std::vector<std::string> &args) {
    if (args.size() != 1) {
        std::cout << RED << "Error: expected no arguments." << ANSI_RESET << std::endl;
        return;
    }

    std::vector<Vertex *> result;
    std::cout << "Calculating result...\n";
    double distance = network->bellmanHeldKarpString(0);

    if(distance < 0) {
        std::cout << YELLOW << "There is no path.\n" << ANSI_RESET;
        end = std::chrono::steady_clock::now();
        return;
    }

    end = std::chrono::steady_clock::now();

    std::cout << "\nDistance: " << distance << std::endl;
}

void Runtime::near(std::vector<std::string> &args) {
    if (args.size() != 1) {
        std::cout << RED << "Error: expected no arguments." << ANSI_RESET << std::endl;
        return;
    }

    std::vector<Vertex *> result;
    std::cout << "Calculating result...\n";
    double distance = network->nearestNeighbour(0, result);

    if((result.size() != network->getVertexSet().size() + 1) || (distance < 0)) {
        std::cout << YELLOW << "There is no path.\n" << ANSI_RESET;
        end = std::chrono::steady_clock::now();
        return;
    }

    end = std::chrono::steady_clock::now();

    std::cout << "Do you want to print the path? [y/N]" << std::endl;
    std::string answer;
    getline(std::cin, answer);
    if (answer == "y") print_path(result);
    std::cout << "\nDistance: " << distance << std::endl;
}

void Runtime::realWorld(std::vector<std::string> &args) {
    unsigned src = getSrc(args);
    if (src == (unsigned) -1) return;

    std::vector<Vertex *> result;
    std::cout << "Calculating result...\n";
    double distance = network->realWorldTSP(0, result);

    if((result.size() != network->getVertexSet().size() + 1) || (distance < 0)) {
        std::cout << YELLOW << "There is no path.\n" << ANSI_RESET;
        end = std::chrono::steady_clock::now();
        return;
    }

    end = std::chrono::steady_clock::now();

    std::cout << "Do you want to print the path? [y/N]" << std::endl;
    std::string answer;
    getline(std::cin, answer);
    if (answer == "y") print_path(result);
    std::cout << "\nDistance: " << distance << std::endl;
}

Runtime::~Runtime() {
    delete network;
}
