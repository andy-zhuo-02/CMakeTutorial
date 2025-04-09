# 创建测试可执行文件
add_executable(test_string_utils test_string_utils.cpp)

target_link_libraries(test_string_utils
    PRIVATE
        string_utils
)

# 添加测试
add_test(
    NAME StringUtilsTest
    COMMAND test_string_utils
) 