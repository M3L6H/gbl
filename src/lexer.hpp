#ifndef gblc_lexer_h
#define gblc_lexer_h

#include <string>

//! Namespace for the gbl compiler
namespace gblc {
  //! Tokens that are recognized by the Lexer.
  enum class TokenType {
    close_paren, //!< Close parentheses
    eof,         //!< End of file marker
    minus,       //!< Hyphen character interpreted as minus symbol
    number,      //!< Any numeric value
    open_paren,  //!< Open parentheses
    plus,        //!< Plus symbol
    slash,       //!< Slash symbol
    star         //!< Asterisk symbol
  };

  /*!
   * @brief Token that is returned by the Lexer.
   *
   * @see Lexer
   */
  struct Token {
    //! The column the first character of this token is in.
    int col;

    //! The line this token was found in.
    int line;

    //! The actual text that was parsed into this token.
    std::string text;

    //! The type of token that was parsed.
    TokenType type;
  };

  //! Class for tokenizing a file or string.
  class Lexer {
    int _position = 0;
    std::string _text;

  public:
    /*!
     * @brief Construct a new Lexer object.
     *
     * @param input Path to a file or some raw text to tokenize
     */
    Lexer(const std::string input);

    Token next_token();
  };
}

#endif
