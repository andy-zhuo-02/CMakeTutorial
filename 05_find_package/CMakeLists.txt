cmake_minimum_required(VERSION 3.14)
project(FindPackageExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Boost库
find_package(Boost 1.65 REQUIRED COMPONENTS system filesystem)

# 检查是否找到Boost
if(Boost_FOUND)
    message(STATUS "找到Boost: ${Boost_VERSION}")
else()
    message(FATAL_ERROR "未找到所需的Boost库")
endif()

# 创建可执行文件
add_executable(boost_demo main.cpp)

# 链接Boost库
target_link_libraries(boost_demo
    PRIVATE
        Boost::system
        Boost::filesystem
)

# 如果使用的是GCC或Clang，需要链接 stdc++fs 来支持std::filesystem
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_link_libraries(boost_demo PRIVATE stdc++fs)
endif()

# 打印Boost库的信息
message(STATUS "Boost包含目录: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost库目录: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost库: ${Boost_LIBRARIES}") 