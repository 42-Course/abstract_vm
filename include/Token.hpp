/**
 * @file Token.hpp
 * @brief Defines the Token class and TokenType enum for lexical analysis.
 */

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

/**
 * @enum TokenType
 * @brief Enumeration of all possible token types in the AbstractVM language.
 *
 * These token types represent the basic building blocks of the assembly language
 * after lexical analysis.
 */
enum class TokenType {
    // Instructions
    PUSH,       ///< Push instruction keyword
    POP,        ///< Pop instruction keyword
    DUMP,       ///< Dump instruction keyword
    ASSERT,     ///< Assert instruction keyword
    ADD,        ///< Add instruction keyword
    SUB,        ///< Subtract instruction keyword
    MUL,        ///< Multiply instruction keyword
    DIV,        ///< Divide instruction keyword
    MOD,        ///< Modulo instruction keyword
    PRINT,      ///< Print instruction keyword
    EXIT,       ///< Exit instruction keyword

    // Types
    INT8,       ///< int8 type keyword
    INT16,      ///< int16 type keyword
    INT32,      ///< int32 type keyword
    FLOAT,      ///< float type keyword
    DOUBLE,     ///< double type keyword

    // Literals and separators
    INTEGER,    ///< Integer literal (e.g., 42, -123)
    DECIMAL,    ///< Decimal literal (e.g., 3.14, -2.5)
    LPAREN,     ///< Left parenthesis '('
    RPAREN,     ///< Right parenthesis ')'
    NEWLINE,    ///< Newline character
    END_INPUT,  ///< End of input marker ";;"
    END_FILE,   ///< End of file marker

    // Special
    COMMENT,    ///< Comment (starting with ';')
    UNKNOWN     ///< Unknown/invalid token
};

/**
 * @class Token
 * @brief Represents a single token in the AbstractVM assembly language.
 *
 * A token is the basic unit produced by the lexer during lexical analysis.
 * Each token has a type, a string value (lexeme), and position information
 * for error reporting.
 *
 * ## Usage Example
 * ```cpp
 * Token tok(TokenType::PUSH, "push", 1, 0);
 * if (tok.getType() == TokenType::PUSH) {
 *     // Handle push instruction
 * }
 * ```
 */
class Token {
public:
    /**
     * @brief Default constructor creating an unknown token.
     */
    Token();

    /**
     * @brief Constructor with type and value.
     * @param type The token type
     * @param value The token's string value (lexeme)
     * @param line Line number where token appears
     * @param column Column number where token starts
     */
    Token(TokenType type, const std::string& value, size_t line, size_t column);

    /**
     * @brief Gets the token type.
     * @return TokenType The type of this token
     */
    TokenType getType() const;

    /**
     * @brief Gets the token's string value (lexeme).
     * @return const std::string& The string representation
     */
    const std::string& getValue() const;

    /**
     * @brief Gets the line number where this token appears.
     * @return size_t The line number (1-indexed)
     */
    size_t getLine() const;

    /**
     * @brief Gets the column number where this token starts.
     * @return size_t The column number (0-indexed)
     */
    size_t getColumn() const;

    /**
     * @brief Converts token type to a human-readable string.
     * @param type The token type to convert
     * @return std::string String representation of the token type
     */
    static std::string tokenTypeToString(TokenType type);

private:
    TokenType _type;        ///< The type of this token
    std::string _value;     ///< The string value (lexeme)
    size_t _line;           ///< Line number (1-indexed)
    size_t _column;         ///< Column number (0-indexed)
};

#endif // TOKEN_HPP
