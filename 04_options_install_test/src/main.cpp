#include <iostream>
#include "string_utils.h"

int main() {
    std::string input;
    
    std::cout << "请输入一个字符串: ";
    std::getline(std::cin, input);
    
    std::cout << "大写转换: " << utils::to_upper(input) << std::endl;
    std::cout << "小写转换: " << utils::to_lower(input) << std::endl;
    std::cout << "反转字符串: " << utils::reverse(input) << std::endl;
    
    if (utils::is_palindrome(input)) {
        std::cout << "这是一个回文!" << std::endl;
    } else {
        std::cout << "这不是一个回文。" << std::endl;
    }
    
    return 0;
} 