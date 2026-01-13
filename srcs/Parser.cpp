#include "Parser.hpp"
#include "Commands.hpp"
#include "AbstractVMException.hpp"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens, bool collectErrors, VirtualMachine* vm)
    : _tokens(tokens), _currentIndex(0), _collectErrors(collectErrors),
      _hasExitInstruction(false), _vm(vm) {}

const Token& Parser::currentToken() const {
    if (_currentIndex >= _tokens.size()) {
        // Return END_FILE token if out of bounds
        static Token endToken(TokenType::END_FILE, "", 0, 0);
        return endToken;
    }
    return _tokens[_currentIndex];
}

const Token& Parser::peekToken() const {
    if (_currentIndex + 1 >= _tokens.size()) {
        static Token endToken(TokenType::END_FILE, "", 0, 0);
        return endToken;
    }
    return _tokens[_currentIndex + 1];
}

void Parser::advance() {
    if (_currentIndex < _tokens.size()) {
        _currentIndex++;
    }
}

bool Parser::expect(TokenType type) {
    if (currentToken().getType() != type) {
        error("Expected " + Token::tokenTypeToString(type) +
              " but got " + Token::tokenTypeToString(currentToken().getType()) +
              " at line " + std::to_string(currentToken().getLine()));
        return false;
    }
    advance();
    return true;
}

void Parser::error(const std::string& message) {
    if (_collectErrors) {
        _errors.push_back(message);
        // Try to recover: skip to next newline
        while (currentToken().getType() != TokenType::NEWLINE &&
               currentToken().getType() != TokenType::END_FILE &&
               currentToken().getType() != TokenType::END_INPUT) {
            advance();
        }
        if (currentToken().getType() == TokenType::NEWLINE) {
            advance();
        }
    } else {
        throw SyntaxException(message);
    }
}

void Parser::skipNewlines() {
    while (currentToken().getType() == TokenType::NEWLINE) {
        advance();
    }
}

std::vector<std::unique_ptr<ICommand>> Parser::parse() {
    std::vector<std::unique_ptr<ICommand>> commands;

    skipNewlines();

    while (currentToken().getType() != TokenType::END_FILE &&
           currentToken().getType() != TokenType::END_INPUT) {

        auto command = parseInstruction();
        if (command) {
            commands.push_back(std::move(command));
        }

        skipNewlines();
    }

    // Check that exit instruction was found
    if (!_hasExitInstruction && !_collectErrors) {
        throw SyntaxException("Program must end with 'exit' instruction");
    } else if (!_hasExitInstruction && _collectErrors) {
        _errors.push_back("Program must end with 'exit' instruction");
    }

    return commands;
}

std::unique_ptr<ICommand> Parser::parseInstruction() {
    TokenType instrType = currentToken().getType();

    switch (instrType) {
        case TokenType::PUSH:
            return parsePush();
        case TokenType::ASSERT:
            return parseAssert();
        case TokenType::POP:
        case TokenType::DUMP:
        case TokenType::ADD:
        case TokenType::SUB:
        case TokenType::MUL:
        case TokenType::DIV:
        case TokenType::MOD:
        case TokenType::PRINT:
        case TokenType::EXIT:
            return parseSimpleInstruction(instrType);
        default:
            error("Unknown instruction '" + currentToken().getValue() +
                  "' at line " + std::to_string(currentToken().getLine()));
            return nullptr;
    }
}

const IOperand* Parser::parseValue() {
    // Expect a type keyword (int8, int16, int32, float, double)
    TokenType typeToken = currentToken().getType();
    eOperandType type;

    switch (typeToken) {
        case TokenType::INT8:
            type = eOperandType::Int8;
            break;
        case TokenType::INT16:
            type = eOperandType::Int16;
            break;
        case TokenType::INT32:
            type = eOperandType::Int32;
            break;
        case TokenType::FLOAT:
            type = eOperandType::Float;
            break;
        case TokenType::DOUBLE:
            type = eOperandType::Double;
            break;
        default:
            error("Expected operand type (int8, int16, int32, float, double) at line " +
                  std::to_string(currentToken().getLine()));
            return nullptr;
    }

    advance(); // consume type keyword

    std::string valueStr;

    // Check for optional parenthesis: float(42) or float (42) or float 42
    if (currentToken().getType() == TokenType::LPAREN) {
        // Parenthesis syntax: float(42) or float (42)
        advance(); // consume '('

        // Expect number
        if (currentToken().getType() != TokenType::INTEGER &&
            currentToken().getType() != TokenType::DECIMAL) {
            error("Expected numeric value at line " +
                  std::to_string(currentToken().getLine()));
            return nullptr;
        }

        valueStr = currentToken().getValue();
        advance(); // consume number

        if (!expect(TokenType::RPAREN)) {
            return nullptr;
        }
    } else if (currentToken().getType() == TokenType::INTEGER ||
               currentToken().getType() == TokenType::DECIMAL) {
        // Shorthand syntax: float 42
        valueStr = currentToken().getValue();
        advance(); // consume number
    } else {
        error("Expected '(' or numeric value after type at line " +
              std::to_string(currentToken().getLine()));
        return nullptr;
    }

    // Create operand using factory
    try {
        return _factory.createOperand(type, valueStr);
    } catch (const std::exception& e) {
        error("Failed to create operand: " + std::string(e.what()));
        return nullptr;
    }
}

std::unique_ptr<ICommand> Parser::parsePush() {
    advance(); // consume 'push'

    const IOperand* operand = parseValue();
    if (!operand) {
        return nullptr;
    }

    return std::make_unique<PushCommand>(operand);
}

std::unique_ptr<ICommand> Parser::parseAssert() {
    advance(); // consume 'assert'

    const IOperand* operand = parseValue();
    if (!operand) {
        return nullptr;
    }

    return std::make_unique<AssertCommand>(operand);
}

std::unique_ptr<ICommand> Parser::parseSimpleInstruction(TokenType type) {
    advance(); // consume instruction keyword

    switch (type) {
        case TokenType::POP:
            return std::make_unique<PopCommand>();
        case TokenType::DUMP:
            return std::make_unique<DumpCommand>();
        case TokenType::ADD:
            return std::make_unique<AddCommand>();
        case TokenType::SUB:
            return std::make_unique<SubCommand>();
        case TokenType::MUL:
            return std::make_unique<MulCommand>();
        case TokenType::DIV:
            return std::make_unique<DivCommand>();
        case TokenType::MOD:
            return std::make_unique<ModCommand>();
        case TokenType::PRINT:
            return std::make_unique<PrintCommand>();
        case TokenType::EXIT:
            _hasExitInstruction = true;
            return std::make_unique<ExitCommand>(_vm);
        default:
            error("Internal error: unexpected instruction type");
            return nullptr;
    }
}

const std::vector<std::string>& Parser::getErrors() const {
    return _errors;
}

bool Parser::hasErrors() const {
    return !_errors.empty();
}
