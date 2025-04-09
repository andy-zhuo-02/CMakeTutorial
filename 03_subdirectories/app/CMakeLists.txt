# 创建可执行文件
add_executable(calc_app main.cpp)

# 链接库
target_link_libraries(calc_app
    PRIVATE
        calculator
) 