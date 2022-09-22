#include "lexer.hpp"

#include <fstream>

using namespace gblc;

Lexer::Lexer(const std::string input) : _text(input) {
  std::ifstream file(input);

  if (!file) {
    // TODO: stream from file
  }

  file.close();
}

Token Lexer::next_token() {

}
