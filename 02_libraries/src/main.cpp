#include <iostream>
#include "math_utils.h"

int main() {
    int a = 10, b = 5;
    
    std::cout << "Math Operations:" << std::endl;
    std::cout << a << " + " << b << " = " << math::add(a, b) << std::endl;
    std::cout << a << " - " << b << " = " << math::subtract(a, b) << std::endl;
    std::cout << a << " * " << b << " = " << math::multiply(a, b) << std::endl;
    std::cout << a << " / " << b << " = " << math::divide(a, b) << std::endl;
    
    return 0;
} 