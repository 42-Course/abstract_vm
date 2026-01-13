#include "AbstractVM.hpp"
#include <iostream>
#include <fstream>

VirtualMachine::VirtualMachine() : _exitCalled(false), _verbose(false), _collectErrors(false) {}

void VirtualMachine::cleanupStack() {
    while (!_stack.empty()) {
        delete _stack.top();
        _stack.pop();
    }
}

VirtualMachine::~VirtualMachine() {
    cleanupStack();
}

void VirtualMachine::validateExit() const {
    if (!_exitCalled) {
        throw AbstractVMException("Error: 'exit' instruction missing.");
    }
}

void VirtualMachine::setVerbose(bool verbose) {
    _verbose = verbose;
}

void VirtualMachine::setCollectErrors(bool collect) {
    _collectErrors = collect;
}

void VirtualMachine::setExitCalled() {
    _exitCalled = true;
}

size_t VirtualMachine::stackSize() const {
    return _stack.size();
}

void VirtualMachine::run(std::istream& input, bool fromStdin) {
    Lexer lexer(input, fromStdin, _collectErrors);
    Parser parser(lexer.tokenize(), _collectErrors, this);
    std::vector<std::unique_ptr<ICommand>> commands = parser.parse();

    // Print collected parser errors if in error collection mode
    if (_collectErrors && parser.hasErrors()) {
        for (const auto& error : parser.getErrors()) {
            std::cerr << "Error: " << error << std::endl;
        }
        return ;
    }

    try {
        executeCommands(commands);
        validateExit();
    } catch (const AbstractVMException& e) {
        if (!_collectErrors) {
            throw;
        } else {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    cleanupStack();
}

void VirtualMachine::runFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file " + filename);
    }
    run(file, false);
}

void VirtualMachine::executeCommands(std::vector<std::unique_ptr<ICommand>>& commands) {
    for (const auto& command : commands) {
        command->execute(_stack);
        if (_verbose) {
            std::cout << "Executed command. Stack size: " << _stack.size() << std::endl;
        }
        if (_exitCalled) {
            break;
        }
    }
}