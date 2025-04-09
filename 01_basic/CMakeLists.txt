# 指定所需的最低CMake版本
cmake_minimum_required(VERSION 3.10)

# 定义项目名称和使用的语言
project(HelloCMake LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件目标
add_executable(hello_app main.cpp)

# 打印一些信息
message(STATUS "配置项目: ${PROJECT_NAME}")
message(STATUS "源代码目录: ${PROJECT_SOURCE_DIR}")
message(STATUS "构建目录: ${PROJECT_BINARY_DIR}") 