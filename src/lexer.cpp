#include "lexer.hpp"

#include <ctype.h>
#include <iostream>

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
 * @throws ValueException
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
 * @throws ValueException
 * @return int
 */
template<>
int Token::value<int>() const {
  if (!_has_value) {
    std::throw_with_nested(ValueException());
  }

  return _int_value;
}

Token::Token(int col, int line, const std::string& text, TokenType type) :
  col(col   + 1),
  line(line + 1),
  text(text),
  type(type) {}

Token::Token(int col, int line, const std::string& text, TokenType type, float value) :
  col(col   + 1),
  line(line + 1),
  text(text),
  type(type),
  _float_value(value),
  _has_value(true) {}

Token::Token(int col, int line, const std::string& text, TokenType type, int value) :
  col(col   + 1),
  line(line + 1),
  text(text),
  type(type),
  _int_value(value),
  _has_value(true) {}

Lexer::Lexer(const std::string input) : _text({ input }) {
  std::ifstream* file = new std::ifstream(input);

  if (file->is_open()) {
    _file = file;
    std::getline(*_file, _text[0]);
    _text[0].append("\n");
  } else {
    _file = nullptr;
    delete file;
  }
}

Lexer::~Lexer() {
  if (_file) delete _file;
}

Token Lexer::next_token() {
  int col  = _col;
  int line = _line;

  if (current() == '\0') return { col, line, "\0", TokenType::eof };

  // Handle numbers
  // TODO: Handle floats/negative numbers
  if (std::isdigit(current())) {
    do { next(); } while (std::isdigit(current()));

    std::string text = _text[0].substr(col, _col - col);

    try {
      return { col, line, text, TokenType::number, std::stoi(text) };
    } catch (const std::invalid_argument& e) {
      std::cout << "Invalid argument: '" << text << "'" << std::endl;
      std::throw_with_nested(e);
    }
  }

  // Handle whitespace
  if (is_whitespace(current())) {
    set_parsing_token(true);
    do { next(); } while (is_whitespace(current()));

    std::string text;
    int temp_col = col;

    for (int i = 0; i < (int)_text.size(); ++i) {
      int end = i < (int)_text.size() - 1 ? _text[i].size() : _col;
      text.append(_text[i].substr(temp_col, end - temp_col));
      temp_col = 0;
    }

    set_parsing_token(false);

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
  char c = current();
  next();
  return { col, line, std::string(1, c), TokenType::error };
}

const char Lexer::current() const {
  if (_col >= (int)_text[_text.size() - 1].size()) return '\0';

  return _text[_text.size() - 1][_col];
}

void Lexer::next() {
  ++_col;

  if (_col >= (int)_text[_text.size() - 1].size() && _file->good()) {
    if (_parsing_token) {
      _text.push_back("");
      std::getline(*_file, _text[_text.size() - 1]);
    } else {
      std::getline(*_file, _text[0]);
    }

    _text[_text.size() - 1].append("\n");
    _col = 0;
    ++_line;
  }
}

void Lexer::set_parsing_token(bool value) {
  _parsing_token = value;

  if (!value && (int)_text.size() > 0) {
    std::string temp = _text[_text.size() - 1];
    _text.clear();
    _text.push_back(temp);
  }
}
