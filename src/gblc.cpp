#include <iostream>
#include <sstream>

#include "lexer.hpp"
#include "utils.cpp"

using namespace gblc;

int main() {
  while (true) {
    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);

    Lexer lexer(input);

    if (is_whitespace_or_empty(input)) break;

    std::cout << input << std::endl;
  }

  return 0;
}
