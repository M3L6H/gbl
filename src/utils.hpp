#ifndef gblc_utils_h
#define gblc_utils_h

#include <string>

namespace gblc {
  /*!
   * @brief Check if a character is a whitespace character.
   *
   * @details Delegates to [std::isspace](https://en.cppreference.com/w/cpp/string/byte/isspace).
   *
   * @param c The character to check
   * @return true
   * @return false
   */
  bool is_whitespace(const char& c);

  /*!
   * @brief Check if a string consists only of whitespace.
   *        Returns false if the string is empty.
   *
   * @param str The string to check
   * @return true
   * @return false
   */
  bool is_whitespace(const std::string& str);

  /*!
   * @brief Returns true if the string consists only of whitespace or is empty.
   *
   * @param str The string to check
   * @return true
   * @return false
   */
  bool is_whitespace_or_empty(const std::string& str);
}

#endif
