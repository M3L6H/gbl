#include "utils.hpp"

#include <cctype>

bool gblc::is_whitespace(const char& c) {
  return std::isspace(c);
}

bool gblc::is_whitespace(const std::string& str) {
  int n = str.size();
  for (int i = 0; i < n; ++i) {
    if (is_whitespace(str[i]) == false) return false;
  }
  return n > 0;
}

bool gblc::is_whitespace_or_empty(const std::string& str) {
  return str.size() == 0 || is_whitespace(str);
}
