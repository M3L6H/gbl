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
      std::cout << "Token: " << (int)token.type << " " << token.text << std::endl;
    }

    if (is_whitespace_or_empty(input)) break;
  }

  return 0;
}
