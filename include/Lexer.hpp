/**
 * @file Lexer.hpp
 * @brief Defines the Lexer class for lexical analysis of AbstractVM programs.
 */

#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <istream>
#include "Token.hpp"

/**
 * @class Lexer
 * @brief Performs lexical analysis on AbstractVM assembly programs.
 *
 * The Lexer (or tokenizer) is responsible for converting raw input text
 * into a sequence of tokens that can be parsed by the Parser class.
 *
 * ## Responsibilities
 *
 * - Read input character by character
 * - Recognize keywords, identifiers, numbers, and symbols
 * - Handle comments (lines starting with ';')
 * - Track line and column numbers for error reporting
 * - Detect the end of input (";;" for stdin, EOF for files)
 *
 * ## Usage Example
 * ```cpp
 * std::istringstream input("push int32(42)\nadd\nexit");
 * Lexer lexer(input);
 * std::vector<Token> tokens = lexer.tokenize();
 * ```
 */
class Lexer {
public:
    /**
     * @brief Constructor with input stream.
     * @param input Reference to the input stream to tokenize
     * @param fromStdin Flag indicating if input is from stdin (handles ";;" marker)
     */
    explicit Lexer(std::istream& input, bool fromStdin = false);

    /**
     * @brief Tokenizes the entire input stream.
     *
     * Reads the input and produces a vector of all tokens found.
     *
     * @return std::vector<Token> Vector containing all tokens in order
     * @throws LexicalException if an invalid character or token is encountered
     */
    std::vector<Token> tokenize();

    /**
     * @brief Gets the next token from the input.
     *
     * Used for incremental tokenization if needed.
     *
     * @return Token The next token from the input
     * @throws LexicalException if an invalid character or token is encountered
     */
    Token nextToken();

private:
    std::istream& _input;   ///< Reference to the input stream
    bool _fromStdin;        ///< Flag for stdin input (handles ";;" terminator)
    size_t _line;           ///< Current line number (1-indexed)
    size_t _column;         ///< Current column number (0-indexed)
    char _currentChar;      ///< The current character being examined
    bool _endReached;       ///< Flag indicating if end of input was reached

    /**
     * @brief Advances to the next character in the input.
     */
    void advance();

    /**
     * @brief Peeks at the next character without consuming it.
     * @return char The next character, or '\0' if at end
     */
    char peek();

    /**
     * @brief Skips whitespace characters (except newlines).
     */
    void skipWhitespace();

    /**
     * @brief Skips a comment line (from ';' to end of line).
     */
    void skipComment();

    /**
     * @brief Reads an identifier or keyword.
     * @return Token The identifier or keyword token
     */
    Token readIdentifier();

    /**
     * @brief Reads a numeric literal (integer or decimal).
     * @return Token The numeric literal token
     */
    Token readNumber();

    /**
     * @brief Determines if a character is a valid identifier start.
     * @param c The character to check
     * @return bool True if valid identifier start character
     */
    bool isIdentifierStart(char c) const;

    /**
     * @brief Determines if a character is a valid identifier continuation.
     * @param c The character to check
     * @return bool True if valid identifier character
     */
    bool isIdentifierChar(char c) const;

    /**
     * @brief Converts a string to its corresponding token type.
     * @param str The string to convert
     * @return TokenType The corresponding token type
     */
    TokenType keywordToTokenType(const std::string& str) const;
};

#endif // LEXER_HPP
