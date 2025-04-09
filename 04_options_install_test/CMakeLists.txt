cmake_minimum_required(VERSION 3.10)
project(OptionsInstallTest VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置安装目录变量
if(WIN32)
    set(DEFAULT_INSTALL_PREFIX "C:/Program Files/${PROJECT_NAME}")
else()
    set(DEFAULT_INSTALL_PREFIX "/usr/local")
endif()

# 如果没有指定安装路径，使用默认路径
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${DEFAULT_INSTALL_PREFIX}" CACHE PATH "安装目录" FORCE)
endif()

# 选项
option(BUILD_TESTS "构建测试" ON)
option(BUILD_DOCS "构建文档" OFF)

# 创建库
add_library(string_utils
    src/string_utils.cpp
)

target_include_directories(string_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 创建可执行文件
add_executable(string_app src/main.cpp)

target_link_libraries(string_app
    PRIVATE
        string_utils
)

# 安装规则
install(TARGETS string_app
    RUNTIME DESTINATION bin
)

install(TARGETS string_utils
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES src/string_utils.h
    DESTINATION include
)

# 测试部分
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif() 