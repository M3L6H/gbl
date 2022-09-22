#include "lexer.hpp"

#include <ctype.h>
#include <fstream>

#include "utils.hpp"

using namespace gblc;

const char* Token::ValueException::what() {
  return "Token does not have a value.";
}

/*!
 * @brief Get the float value of this token.
 *
 * @details Only makes sense with tokens of the number type.
 *
 * @return float
 */
template<>
float Token::value<float>() const {
  if (!_has_value) {
    std::throw_with_nested(ValueException());
  }

  return _float_value;
}

/*!
 * @brief Get the int value of this token.
 *
 * @details Only makes sense with tokens of the number type.
 *
 * @return int
 */
template<>
int Token::value<int>() const {
  return _int_value;
}

Token::Token(int col, int line, std::string text, TokenType type) :
  col(col),
  line(line),
  text(text),
  type(type) {}

Token::Token(int col, int line, std::string text, TokenType type, float value) :
  col(col),
  line(line),
  text(text),
  type(type),
  _float_value(value),
  _has_value(true) {}

Token::Token(int col, int line, std::string text, TokenType type, int value) :
  col(col),
  line(line),
  text(text),
  type(type),
  _int_value(value),
  _has_value(true) {}

Lexer::Lexer(const std::string input) : _text(input) {
  std::ifstream file(input);

  if (!file) {
    // TODO: stream from file
  }

  file.close();
}

Token Lexer::next_token() {
  int col  = _col;
  int line = _line;

  if (current() == '\0') {
    return { col, line, "", TokenType::eof };
  }

  // Handle numbers
  // TODO: Handle floats/negative numbers
  if (std::isdigit(current())) {
    do { next(); } while (std::isdigit(current()));

    std::string text = _text.substr(col, _col - col);

    return { col, line, text, TokenType::number, std::stoi(text) };
  }

  // Handle whitespace
  if (is_whitespace(current())) {
    do { next(); } while (is_whitespace(current()));

    std::string text = _text.substr(col, _col - col);

    return { col, line, text, TokenType::whitespace };
  }

  // Match single characters
  switch(current()) {
    case '(': next(); return { col, line, "(", TokenType::open_paren  };
    case ')': next(); return { col, line, ")", TokenType::close_paren };
    case '+': next(); return { col, line, "+", TokenType::plus        };
    case '-': next(); return { col, line, "-", TokenType::minus       };
    case '*': next(); return { col, line, "*", TokenType::star        };
    case '/': next(); return { col, line, "/", TokenType::slash       };
    case '%': next(); return { col, line, "%", TokenType::modulo      };
  }

  // Unrecognized token
  next();
  return { col, line, _text.substr(col, 1), TokenType::error };
}

const char Lexer::current() const {
  if (_col >= (int)_text.size()) return '\0';

  return _text[_col];
}

void Lexer::next() {
  ++_col;
}
