#ifndef gblc_lexer_h
#define gblc_lexer_h

#include <string>

namespace gblc {
  /**
   * @brief Tokens that are recognized by the Lexer.
   */
  enum TokenType {
    close_paren,
    eof,
    minus,
    number,
    open_paren,
    plus,
    slash,
    star
  };

  /**
   * @brief Token that is returned by the Lexer.
   *
   * @see Lexer
   */
  struct Token {
    /**
     * @brief The column the first character of this token is in.
     */
    int col;

    /**
     * @brief The line this token was found in.
     */
    int line;

    /**
     * @brief The actual text that was parsed into this token.
     */
    std::string text;

    /**
     * @brief The type of token that was parsed.
     */
    TokenType type;
  };

  /**
   * @brief Class for tokenizing a file or string.
   */
  class Lexer {
    int _position = 0;
    std::string _text;

  public:
    /**
     * @brief Construct a new Lexer object.
     *
     * @param input Path to a file or some raw text to tokenize
     */
    Lexer(const std::string input);

    Token next_token();
  };
}

#endif
