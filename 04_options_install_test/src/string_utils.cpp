#include "string_utils.h"
#include <algorithm>
#include <cctype>

namespace utils {
    std::string to_upper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
                      [](unsigned char c){ return std::toupper(c); });
        return result;
    }
    
    std::string to_lower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
                      [](unsigned char c){ return std::tolower(c); });
        return result;
    }
    
    std::string reverse(const std::string& str) {
        std::string result = str;
        std::reverse(result.begin(), result.end());
        return result;
    }
    
    bool is_palindrome(const std::string& str) {
        std::string clean_str;
        // 移除非字母数字字符并转换为小写
        for (char c : str) {
            if (std::isalnum(c)) {
                clean_str.push_back(std::tolower(c));
            }
        }
        
        std::string reversed = clean_str;
        std::reverse(reversed.begin(), reversed.end());
        
        return clean_str == reversed;
    }
} 