#include <iostream>
#include <sstream>

#include "lexer.hpp"
#include "utils.hpp"

using namespace gblc;

int main() {
  while (true) {
    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);

    Lexer lexer(input);
    while (true) {
      auto token = lexer.next_token();
      if (token.type == TokenType::eof) break;
      std::cout << "L" << token.line << "C" << token.col << ": " << (int)token.type << " '" << token.text << "'";
      try {
        std::cout << " " << token.value<int>();
      } catch(const Token::ValueException&) {}
      std::cout << std::endl;
    }

    if (is_whitespace_or_empty(input)) break;
  }

  return 0;
}
