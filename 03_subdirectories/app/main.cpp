#include <iostream>
#include "calculator.h"

int main() {
    Calculator calc;
    
    double a = 10.5, b = 5.2;
    
    std::cout << "计算器示例：" << std::endl;
    std::cout << a << " + " << b << " = " << calc.add(a, b) << std::endl;
    std::cout << a << " - " << b << " = " << calc.subtract(a, b) << std::endl;
    std::cout << a << " * " << b << " = " << calc.multiply(a, b) << std::endl;
    std::cout << a << " / " << b << " = " << calc.divide(a, b) << std::endl;
    
    return 0;
} 