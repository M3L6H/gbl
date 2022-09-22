#ifndef gblc_utils
#define gblc_utils

#include <string>

/**
 * @brief Check if a character is a whitespace character.
 *
 * @param c The character to check
 * @return true
 * @return false
 */
bool is_whitespace(char c) {
  return c == ' ' || c == '\n' || c == '\t';
}

/**
 * @brief Check if a string consists only of whitespace.
 *        Returns false if the string is empty.
 *
 * @param str The string to check
 * @return true
 * @return false
 */
bool is_whitespace(std::string str) {
  int n = str.size();
  for (int i = 0; i < n; ++i) {
    if (is_whitespace(str[i]) == false) return false;
  }
  return n > 0;
}

/**
 * @brief Returns true if the string consists only of whitespace or is empty.
 *
 * @param str The string to check
 * @return true
 * @return false
 */
bool is_whitespace_or_empty(std::string str) {
  return str.size() == 0 || is_whitespace(str);
}

#endif
