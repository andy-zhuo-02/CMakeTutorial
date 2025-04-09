#include <iostream>
#include <cassert>
#include <string>
#include "../src/string_utils.h"

void test_to_upper() {
    assert(utils::to_upper("hello") == "HELLO");
    assert(utils::to_upper("Hello World") == "HELLO WORLD");
    assert(utils::to_upper("123") == "123");
    std::cout << "to_upper 测试通过" << std::endl;
}

void test_to_lower() {
    assert(utils::to_lower("HELLO") == "hello");
    assert(utils::to_lower("Hello World") == "hello world");
    assert(utils::to_lower("123") == "123");
    std::cout << "to_lower 测试通过" << std::endl;
}

void test_reverse() {
    assert(utils::reverse("hello") == "olleh");
    assert(utils::reverse("Hello World") == "dlroW olleH");
    assert(utils::reverse("12345") == "54321");
    std::cout << "reverse 测试通过" << std::endl;
}

void test_is_palindrome() {
    assert(utils::is_palindrome("level") == true);
    assert(utils::is_palindrome("A man, a plan, a canal: Panama") == true);
    assert(utils::is_palindrome("hello") == false);
    std::cout << "is_palindrome 测试通过" << std::endl;
}

int main() {
    test_to_upper();
    test_to_lower();
    test_reverse();
    test_is_palindrome();
    
    std::cout << "所有测试通过!" << std::endl;
    return 0;
} 