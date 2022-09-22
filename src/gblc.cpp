#include <iostream>
#include <sstream>

#include "utils.cpp"

int main() {
  while (true) {
    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);

    if (is_whitespace_or_empty(input)) break;

    std::cout << input << std::endl;
  }

  return 0;
}
