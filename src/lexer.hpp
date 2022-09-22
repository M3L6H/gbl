#ifndef gblc_lexer_h
#define gblc_lexer_h

#include <fstream>
#include <string>
#include <vector>

//! Namespace for the gbl compiler
namespace gblc {
  //! Tokens that are recognized by the Lexer.
  enum class TokenType {
    close_paren, //!< Close parentheses
    error,       //!< Unrecognized token
    eof,         //!< End of file marker
    minus,       //!< Hyphen character interpreted as minus symbol
    modulo,      //!< Percent character interpreted as modulo symbol
    number,      //!< Any numeric value
    open_paren,  //!< Open parentheses
    plus,        //!< Plus symbol
    slash,       //!< Slash symbol
    star,        //!< Asterisk symbol
    whitespace   //!< Whitespace
  };

  /*!
   * @brief Token that is returned by the Lexer.
   *
   * @see Lexer
   */
  struct Token {
    /*!
     * @brief Exception thrown when the value getter is called on a value-less
     *        token.
     */
    class ValueException : public std::exception {
    public:

      //! Override base what() with custom message
      const char* what();
    };

    //! The column the first character of this token is in.
    int col;

    //! The line this token was found in.
    int line;

    //! The actual text that was parsed into this token.
    std::string text;

    //! The type of token that was parsed.
    TokenType type;

    /*!
     * @brief Get the value of the token.
     *
     * @details Note that calling this getter only makes sense in the case of
     *          a Token that has a value, such as a number token. Calling it for
     *          a Token that lacks such a value creates an exception.
     *
     * @throws ValueException
     * @tparam T The desired value type
     * @returns The value of the token
     */
    template <typename T>
    T value() const;

    /*!
     * @brief Construct a new Token object.
     *
     * @details col and line are both expected to be 0-based indices.
     *
     * @param col  The column the first character of the token is at
     * @param line The line the token is on
     * @param text The text comprising the token
     * @param type The type of the token
     */
    Token(int col, int line, const std::string& text, TokenType type);

    /*!
     * @brief Construct a new Token object with a float value.
     *
     * @param col   The column the first character of the token is at
     * @param line  The line the token is on
     * @param text  The text comprising the token
     * @param type  The type of the token
     * @param value The float value of the token
     */
    Token(int col, int line, const std::string& text, TokenType type, float value);

    /*!
     * @brief Construct a new Token object with an int value.
     *
     * @param col   The column the first character of the token is at
     * @param line  The line the token is on
     * @param text  The text comprising the token
     * @param type  The type of the token
     * @param value The int value of the token
     */
    Token(int col, int line, const std::string& text, TokenType type, int value);

  private:
    float _float_value;
    int   _int_value;

    bool  _has_value = false;
  };

  //! Class for tokenizing a file or string.
  class Lexer {
    int _col  = 0;
    int _line = 0;

    bool _parsing_token = false;

    std::ifstream*            _file;
    std::vector<std::string>  _text;

  public:
    /*!
     * @brief Construct a new Lexer object.
     *
     * @details If raw text is being passed to the Lexer, it should only be a
     *          single line of text.
     *
     * @param input Path to a file or some raw text to tokenize
     */
    Lexer(const std::string input);

    //! Lexer destructor
    virtual ~Lexer();

    /*!
     * @brief Get the next token in the input and advance the Lexer.
     *
     * @return Token
     */
    Token next_token();

  private:
    /*!
     * @brief Get the current character the Lexer is on.
     *
     * @returns The character at _col, _line in the Lexer's input
     */
    const char current() const;

    //! Advance the Lexer by one character
    void next();

    //! Setter for _parsing_token
    void set_parsing_token(bool value);
  };
}

#endif
