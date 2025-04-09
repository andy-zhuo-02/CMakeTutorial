cmake_minimum_required(VERSION 3.10)
project(SubdirExample VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加子目录
add_subdirectory(lib)
add_subdirectory(app)

# 演示如何增加选项
option(BUILD_DOCS "构建文档" OFF)

if(BUILD_DOCS)
    message(STATUS "将生成文档")
    # 这里可以添加文档生成的相关命令
endif() 