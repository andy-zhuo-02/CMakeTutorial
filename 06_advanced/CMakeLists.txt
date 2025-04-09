cmake_minimum_required(VERSION 3.14)
project(AdvancedExample VERSION 2.3.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 配置文件生成
configure_file(
    src/config.h.in
    ${CMAKE_BINARY_DIR}/generated/config.h
)

# 创建可执行文件
add_executable(advanced_app src/main.cpp)

# 包含生成的头文件目录
target_include_directories(advanced_app
    PRIVATE
        ${CMAKE_BINARY_DIR}/generated
)

# 使用生成器表达式添加预处理器宏
target_compile_definitions(advanced_app
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG_BUILD>
)

# 根据构建类型使用不同的编译器标志
target_compile_options(advanced_app
    PRIVATE
        $<$<CONFIG:Debug>:-DDEBUG=1>
        $<$<CONFIG:Release>:-DNDEBUG>
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
)

# 添加一个自定义命令，在构建后运行
add_custom_command(
    TARGET advanced_app
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "构建完成: $<TARGET_FILE:advanced_app>"
    COMMENT "显示构建信息"
)

# 添加一个自定义目标
add_custom_target(run_app
    COMMAND advanced_app
    DEPENDS advanced_app
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "运行应用程序"
) 