/**
 * @file Parser.hpp
 * @brief Defines the Parser class for syntactic analysis of AbstractVM programs.
 */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <memory>
#include "Token.hpp"
#include "ICommand.hpp"
#include "OperandFactory.hpp"

// Forward declaration
class VirtualMachine;

/**
 * @class Parser
 * @brief Performs syntactic analysis and generates commands from tokens.
 *
 * The Parser takes a sequence of tokens produced by the Lexer and
 * validates that they conform to the AbstractVM grammar. It then
 * generates executable command objects that can be run by the VirtualMachine.
 *
 * ## Grammar
 *
 * The parser implements the following grammar:
 * ```
 * S := INSTR [SEP INSTR]* #
 *
 * INSTR :=
 *     push VALUE
 *   | pop
 *   | dump
 *   | assert VALUE
 *   | add
 *   | sub
 *   | mul
 *   | div
 *   | mod
 *   | print
 *   | exit
 *
 * VALUE :=
 *     int8(N)
 *   | int16(N)
 *   | int32(N)
 *   | float(Z)
 *   | double(Z)
 *
 * N := [-]?[0..9]+
 * Z := [-]?[0..9]+.[0..9]+
 * SEP := '\n'+
 * ```
 *
 * ## Error Handling
 *
 * The parser can operate in two modes:
 * - **Fail-fast**: Stops at the first error (default)
 * - **Error collection**: Continues parsing and collects all errors (bonus)
 *
 * ## Usage Example
 * ```cpp
 * Lexer lexer(input);
 * std::vector<Token> tokens = lexer.tokenize();
 * VirtualMachine vm;
 * Parser parser(tokens, false, &vm);
 * std::vector<std::unique_ptr<ICommand>> commands = parser.parse();
 * ```
 */
class Parser {
public:
    /**
     * @brief Constructor with token vector.
     * @param tokens Vector of tokens to parse
     * @param collectErrors If true, collects all errors instead of failing fast
     * @param vm Pointer to the VirtualMachine instance (needed for ExitCommand)
     */
    explicit Parser(const std::vector<Token>& tokens, bool collectErrors = false, VirtualMachine* vm = nullptr);

    /**
     * @brief Parses the tokens and generates commands.
     *
     * Validates the token sequence against the grammar and produces
     * a vector of executable commands.
     *
     * @return std::vector<std::unique_ptr<ICommand>> Vector of parsed commands
     * @throws SyntaxException if a syntax error is encountered (fail-fast mode)
     */
    std::vector<std::unique_ptr<ICommand>> parse();

    /**
     * @brief Gets all collected errors (in error collection mode).
     * @return const std::vector<std::string>& Vector of error messages
     */
    const std::vector<std::string>& getErrors() const;

    /**
     * @brief Checks if any errors were collected.
     * @return bool True if errors exist
     */
    bool hasErrors() const;

private:
    std::vector<Token> _tokens;                     ///< The tokens to parse
    size_t _currentIndex;                           ///< Current position in token vector
    bool _collectErrors;                            ///< Error collection mode flag
    std::vector<std::string> _errors;               ///< Collected error messages
    OperandFactory _factory;                        ///< Factory for creating operands
    bool _hasExitInstruction;                       ///< Flag tracking if exit was found
    VirtualMachine* _vm;                            ///< Pointer to the VirtualMachine

    /**
     * @brief Gets the current token.
     * @return const Token& Reference to the current token
     */
    const Token& currentToken() const;

    /**
     * @brief Gets the next token without advancing.
     * @return const Token& Reference to the next token
     */
    const Token& peekToken() const;

    /**
     * @brief Advances to the next token.
     */
    void advance();

    /**
     * @brief Checks if current token matches expected type and advances.
     * @param type The expected token type
     * @return bool True if matched
     * @throws SyntaxException if type doesn't match (fail-fast mode)
     */
    bool expect(TokenType type);

    /**
     * @brief Reports a syntax error.
     * @param message The error message
     * @throws SyntaxException in fail-fast mode
     */
    void error(const std::string& message);

    /**
     * @brief Skips newline tokens.
     */
    void skipNewlines();

    /**
     * @brief Parses a single instruction.
     * @return std::unique_ptr<ICommand> The parsed command, or nullptr on error
     */
    std::unique_ptr<ICommand> parseInstruction();

    /**
     * @brief Parses a value specification (type and value).
     * @return const IOperand* The created operand
     * @throws SyntaxException if value format is invalid
     */
    const IOperand* parseValue();

    /**
     * @brief Parses a push instruction.
     * @return std::unique_ptr<ICommand> The push command
     */
    std::unique_ptr<ICommand> parsePush();

    /**
     * @brief Parses an assert instruction.
     * @return std::unique_ptr<ICommand> The assert command
     */
    std::unique_ptr<ICommand> parseAssert();

    /**
     * @brief Parses a simple instruction (no operands).
     * @param type The instruction token type
     * @return std::unique_ptr<ICommand> The command
     */
    std::unique_ptr<ICommand> parseSimpleInstruction(TokenType type);
};

#endif // PARSER_HPP
