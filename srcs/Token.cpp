#include "Token.hpp"

Token::Token() : _type(TokenType::UNKNOWN), _value(""), _line(0), _column(0) {}


Token::Token(TokenType type, const std::string& value, size_t line, size_t column)
    : _type(type), _value(value), _line(line), _column(column) {}

TokenType Token::getType() const {
    return _type;
}

const std::string& Token::getValue() const {
    return _value;
}

size_t Token::getLine() const {
    return _line;
}

size_t Token::getColumn() const {
    return _column;
}

std::string Token::tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::PUSH: return "PUSH";
        case TokenType::POP: return "POP";
        case TokenType::DUMP: return "DUMP";
        case TokenType::ASSERT: return "ASSERT";
        case TokenType::ADD: return "ADD";
        case TokenType::SUB: return "SUB";
        case TokenType::MUL: return "MUL";
        case TokenType::DIV: return "DIV";
        case TokenType::MOD: return "MOD";
        case TokenType::PRINT: return "PRINT";
        case TokenType::EXIT: return "EXIT";
        case TokenType::INT8: return "INT8";
        case TokenType::INT16: return "INT16";
        case TokenType::INT32: return "INT32";
        case TokenType::FLOAT: return "FLOAT";
        case TokenType::DOUBLE: return "DOUBLE";
        case TokenType::INTEGER: return "INTEGER";
        case TokenType::DECIMAL: return "DECIMAL";
        case TokenType::LPAREN: return "LPAREN";
        case TokenType::RPAREN: return "RPAREN";
        case TokenType::NEWLINE: return "NEWLINE";
        case TokenType::END_INPUT: return "END_INPUT";
        case TokenType::END_FILE: return "END_FILE";
        case TokenType::COMMENT: return "COMMENT";
        case TokenType::UNKNOWN: return "UNKNOWN";
        default: return "INVALID_TOKEN_TYPE";
    }
}