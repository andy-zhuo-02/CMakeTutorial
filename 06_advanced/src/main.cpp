#include <iostream>
#include "config.h"

int main() {
    std::cout << "项目名称: " << PROJECT_NAME << std::endl;
    std::cout << "项目版本: " << PROJECT_VERSION << std::endl;
    std::cout << "主版本号: " << PROJECT_VERSION_MAJOR << std::endl;
    std::cout << "次版本号: " << PROJECT_VERSION_MINOR << std::endl;
    
#ifdef DEBUG_BUILD
    std::cout << "这是调试构建" << std::endl;
#else
    std::cout << "这是发布构建" << std::endl;
#endif
    
    return 0;
} 