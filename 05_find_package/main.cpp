#include <iostream>
#include <filesystem>
#include <boost/algorithm/string.hpp>

int main() {
    // 使用Boost库
    std::string str = "Hello, World!";
    std::cout << "原始字符串: " << str << std::endl;
    
    boost::to_upper(str);
    std::cout << "使用Boost处理后: " << str << std::endl;
    
    // 使用c++17 filesystem
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::cout << "当前路径: " << currentPath << std::endl;
    
    return 0;
} 