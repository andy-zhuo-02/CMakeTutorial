cmake_minimum_required(VERSION 3.10)
project(LibraryExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 创建一个静态库，命名为math_utils
add_library(math_utils STATIC 
    src/math_utils.cpp
)

# 为库指定包含目录
target_include_directories(math_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 添加可执行文件
add_executable(math_app src/main.cpp)

# 链接库到可执行文件
target_link_libraries(math_app
    PRIVATE
        math_utils
)

# 演示如何创建动态库（共享库）
option(BUILD_SHARED_LIBRARY "构建共享库版本" OFF)

if(BUILD_SHARED_LIBRARY)
    # 创建一个共享库
    add_library(math_utils_shared SHARED
        src/math_utils.cpp
    )
    
    # 为共享库设置属性
    set_target_properties(math_utils_shared
        PROPERTIES
        OUTPUT_NAME "math_utils" # 输出文件名
        VERSION 1.0.0            # 版本号
        SOVERSION 1              # API版本
    )
    
    # 为共享库指定包含目录
    target_include_directories(math_utils_shared
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    
    # 创建使用共享库的可执行文件
    add_executable(math_app_shared src/main.cpp)
    
    # 链接共享库
    target_link_libraries(math_app_shared
        PRIVATE
            math_utils_shared
    )
endif() 