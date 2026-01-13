/**
 * @file main.cpp
 * @brief Entry point for the AbstractVM program.
 */

#include <iostream>
#include <fstream>
#include "VirtualMachine.hpp"

int main(int argc, char** argv) {
    try {
        VirtualMachine vm;

        if (argc == 2) {
            // Run from file
            vm.runFile(argv[1]);
        } else if (argc == 1) {
            // Run from stdin
            std::cout << "Reading from stdin. End with ';;'" << std::endl;
            vm.run(std::cin, true);
        } else {
            std::cerr << "Usage: " << argv[0] << " [file]" << std::endl;
            return 1;
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
