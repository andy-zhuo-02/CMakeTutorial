# 创建库
add_library(calculator
    src/calculator.cpp
)

# 为库指定包含目录
target_include_directories(calculator
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
) 