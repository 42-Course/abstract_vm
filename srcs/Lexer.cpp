#include "AbstractVM.hpp"
#include <cctype>

Lexer::Lexer(std::istream& input, bool fromStdin, bool collectErrors)
    : _input(input), _fromStdin(fromStdin), _line(1), _column(1),
      _currentChar('\0'), _endReached(false), _collectErrors(collectErrors) {}

void Lexer::advance() {
    if (_endReached) {
        return;
    }
    if (_input.get(_currentChar)) {
        if (_currentChar == '\n') {
            _line++;
            _column = 1;
        } else {
            _column++;
        }
    } else {
        _endReached = true;
        _currentChar = '\0';
    }
}

char Lexer::peek() {
    if (_endReached) {
        return '\0';
    }
    char nextChar = _input.peek();
    return _input.eof() ? '\0' : nextChar;
}

void Lexer::skipWhitespace() {
    while (std::isspace(_currentChar) && _currentChar != '\n' && !_endReached) {
        advance();
    }
}

void Lexer::skipComment() {
    while (_currentChar != '\n' && !_endReached) {
        advance();
    }
}

Token Lexer::readIdentifier() {
    std::string value;
    size_t startColumn = _column;

    while (isIdentifierChar(_currentChar) && !_endReached) {
        value += _currentChar;
        advance();
    }

    TokenType type = keywordToTokenType(value);
    return Token(type, value, _line, startColumn);
}

Token Lexer::readNumber() {
    std::string value;
    size_t startColumn = _column;
    bool isDecimal = false;

    if (_currentChar == '-' || _currentChar == '+') {
        value += _currentChar;
        advance();
    }

    while (std::isdigit(_currentChar) && !_endReached) {
        value += _currentChar;
        advance();
    }

    if (_currentChar == '.') {
        isDecimal = true;
        value += _currentChar;
        advance();

        while (std::isdigit(_currentChar) && !_endReached) {
            value += _currentChar;
            advance();
        }
    }

    TokenType type = isDecimal ? TokenType::DECIMAL : TokenType::INTEGER;
    return Token(type, value, _line, startColumn);
}

bool Lexer::isIdentifierStart(char c) const {
    return std::isalpha(c);
}

bool Lexer::isIdentifierChar(char c) const {
    return std::isalnum(c);
}

TokenType Lexer::keywordToTokenType(const std::string& str) const {
    if (str == "push") return TokenType::PUSH;
    if (str == "pop") return TokenType::POP;
    if (str == "dump") return TokenType::DUMP;
    if (str == "assert") return TokenType::ASSERT;
    if (str == "add") return TokenType::ADD;
    if (str == "sub") return TokenType::SUB;
    if (str == "mul") return TokenType::MUL;
    if (str == "div") return TokenType::DIV;
    if (str == "mod") return TokenType::MOD;
    if (str == "print") return TokenType::PRINT;
    if (str == "exit") return TokenType::EXIT;
    if (str == "int8") return TokenType::INT8;
    if (str == "int16") return TokenType::INT16;
    if (str == "int32") return TokenType::INT32;
    if (str == "float") return TokenType::FLOAT;
    if (str == "double") return TokenType::DOUBLE;
    return TokenType::UNKNOWN;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    advance(); // Initialize _currentChar

    Token token = nextToken();
    while (token.getType() != TokenType::END_FILE && token.getType() != TokenType::END_INPUT) {
        if (token.getType() != TokenType::COMMENT) {
            tokens.push_back(token);
        }
        token = nextToken();
    }

    tokens.push_back(token); // Add END_FILE or END_INPUT
    return tokens;
}

Token Lexer::nextToken() {
    skipWhitespace();

    if (_endReached) {
        return Token(TokenType::END_FILE, "", _line, _column);
    }

    // Check for ";;" (end of stdin input)
    if (_fromStdin && _currentChar == ';' && peek() == ';') {
        size_t startColumn = _column;
        advance(); // consume first ';'
        advance(); // consume second ';'
        return Token(TokenType::END_INPUT, ";;", _line, startColumn);
    }

    // Comments start with ';'
    if (_currentChar == ';') {
        size_t startColumn = _column;
        skipComment();
        return Token(TokenType::COMMENT, ";", _line, startColumn);
    }

    // Newline
    if (_currentChar == '\n') {
        size_t startColumn = _column;
        advance();
        return Token(TokenType::NEWLINE, "\\n", _line, startColumn);
    }

    // Left parenthesis
    if (_currentChar == '(') {
        size_t startColumn = _column;
        advance();
        return Token(TokenType::LPAREN, "(", _line, startColumn);
    }

    // Right parenthesis
    if (_currentChar == ')') {
        size_t startColumn = _column;
        advance();
        return Token(TokenType::RPAREN, ")", _line, startColumn);
    }

    // Numbers (including negative)
    if (std::isdigit(_currentChar) ||
        (_currentChar == '-' && std::isdigit(peek())) ||
        (_currentChar == '+' && std::isdigit(peek()))) {
        return readNumber();
    }

    // Identifiers and keywords
    if (isIdentifierStart(_currentChar)) {
        return readIdentifier();
    }

    // Unknown character
    std::string unknownChar(1, _currentChar);
    size_t startColumn = _column;
    std::string errorMsg = "Unexpected character '" + unknownChar +
                          "' at line " + std::to_string(_line) +
                          ", column " + std::to_string(startColumn);

    if (_collectErrors) {
        // Store error and try to recover
        _errors.push_back(errorMsg);
        skipToRecoverableState();
        return Token(TokenType::UNKNOWN, unknownChar, _line, startColumn);
    } else {
        // Fail-fast mode: throw immediately
        advance();
        throw LexicalException(errorMsg);
    }
}

void Lexer::setCollectErrors(bool collect) {
    _collectErrors = collect;
}

const std::vector<std::string>& Lexer::getErrors() const {
    return _errors;
}

bool Lexer::hasErrors() const {
    return !_errors.empty();
}

void Lexer::skipToRecoverableState() {
    // Skip to next newline or end of input for error recovery
    while (_currentChar != '\n' && !_endReached) {
        advance();
    }
    // Consume the newline if present
    if (_currentChar == '\n') {
        advance();
    }
}