#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>

namespace utils {
    std::string to_upper(const std::string& str);
    std::string to_lower(const std::string& str);
    std::string reverse(const std::string& str);
    bool is_palindrome(const std::string& str);
}

#endif // STRING_UTILS_H 