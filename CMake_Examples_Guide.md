# CMake 学习示例详细解析

本文档详细解析CMake学习示例项目中的各个示例，帮助您深入理解CMake的核心概念和使用方法。

## 示例1：基础命令 - Hello World

### 目录结构

```
01_basic/
├── CMakeLists.txt    # CMake构建脚本
└── main.cpp          # 简单的C++源文件
```

### 源代码解析

**main.cpp**:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, CMake world!" << std::endl;
    return 0;
}
```

这是一个最简单的C++程序，仅打印一条"Hello, CMake world!"信息。我们将使用CMake来构建这个程序。

### CMakeLists.txt 详解

```cmake
# 指定所需的最低CMake版本
cmake_minimum_required(VERSION 3.10)

# 定义项目名称和使用的语言
project(HelloCMake LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件目标
add_executable(hello_app main.cpp)

# 打印一些信息
message(STATUS "配置项目: ${PROJECT_NAME}")
message(STATUS "源代码目录: ${PROJECT_SOURCE_DIR}")
message(STATUS "构建目录: ${PROJECT_BINARY_DIR}")
```

#### 命令详解：

1. **cmake_minimum_required(VERSION 3.10)**

   - **作用**：声明构建此项目所需的最低CMake版本
   - **重要性**：如果用户的CMake版本低于指定版本，将终止配置过程并显示错误信息
   - **最佳实践**：
     - 这应该是CMakeLists.txt的第一个命令
     - 选择一个合理的最低版本，既能支持你需要的功能，又不要求用户安装太新的版本
     - 版本号格式为 `主版本.次版本[.补丁版本]`
   - **版本影响**：不同版本的CMake可能有不同的默认行为和可用功能，指定版本可确保脚本在不同环境中有一致的行为
2. **project(HelloCMake LANGUAGES CXX)**

   - **作用**：定义项目的基本信息
   - **参数解析**：
     - `HelloCMake`：项目名称
     - `LANGUAGES CXX`：指定项目使用C++语言（CXX是C++的CMake标识符）
   - **可选参数**：
     - `VERSION x.y.z`：指定项目版本号
     - `DESCRIPTION "文本"`：项目描述
     - `HOMEPAGE_URL "URL"`：项目主页
   - **自动定义的变量**：
     - `PROJECT_NAME`：项目名称（此例中为"HelloCMake"）
     - `PROJECT_SOURCE_DIR`：包含项目主CMakeLists.txt的目录（绝对路径）
     - `PROJECT_BINARY_DIR`：项目构建目录（绝对路径）
     - 如果指定了VERSION，还会定义：`PROJECT_VERSION`、`PROJECT_VERSION_MAJOR`、`PROJECT_VERSION_MINOR`等
3. **set(CMAKE_CXX_STANDARD 11)**

   - **作用**：设置C++标准版本为C++11
   - **说明**：这是一个特殊的CMake变量，影响编译器的 `-std=c++11`或等效标志
   - **常见值**：`98`、`11`、`14`、`17`、`20`、`23`等
4. **set(CMAKE_CXX_STANDARD_REQUIRED ON)**

   - **作用**：规定必须使用指定的C++标准
   - **效果**：如果编译器不支持指定的C++标准，CMake将报错而不是默默地使用旧标准
5. **add_executable(hello_app main.cpp)**

   - **作用**：定义一个名为 `hello_app`的可执行文件目标
   - **参数解析**：
     - `hello_app`：目标名称，也是生成的可执行文件名（Windows上会自动加上.exe）
     - `main.cpp`：构建此目标所需的源文件
   - **扩展用法**：
     - 可以指定多个源文件：`add_executable(目标名 源文件1 源文件2 ...)`
     - 可以使用变量：`add_executable(目标名 ${SOURCE_FILES})`
6. **message命令**

   - **作用**：在CMake配置阶段输出信息
   - **级别含义**：
     - `STATUS`：普通信息，命令行中会以 `--`前缀显示
     - `WARNING`：警告信息，但不会中断处理
     - `FATAL_ERROR`：错误信息，会中断CMake处理
   - **变量引用**：通过 `${变量名}`语法引用变量值

### 构建和运行过程

1. **创建构建目录**：

   ```bash
   mkdir -p 01_basic/build
   cd 01_basic/build
   ```

   - **为什么需要单独的构建目录**：
     - 源代码和构建产物分离，保持源码目录干净
     - 支持多种构建配置（如Debug/Release）共存
     - 便于删除所有构建产物（只需删除构建目录）
     - 被称为"外部构建"(out-of-source build)，是CMake的最佳实践
2. **配置阶段**：

   ```bash
   cmake ..
   ```

   - **过程说明**：

     - CMake读取上层目录的CMakeLists.txt文件
     - 检测编译器和环境
     - 生成本地构建系统（如Makefiles、Visual Studio解决方案等）
     - 将配置存储在CMakeCache.txt中
   - **常用选项**：

     - 指定生成器：`cmake -G "生成器名称" ..`
       - 例如：`cmake -G "Ninja" ..` 或 `cmake -G "Visual Studio 17 2022" ..`
     - 指定构建类型：`cmake -DCMAKE_BUILD_TYPE=类型 ..`
       - 例如：`cmake -DCMAKE_BUILD_TYPE=Debug ..` 或 `cmake -DCMAKE_BUILD_TYPE=Release ..`
     - 指定安装前缀：`cmake -DCMAKE_INSTALL_PREFIX=/安装路径 ..`
3. **构建阶段**：

   ```bash
   cmake --build .
   ```

   - **过程说明**：

     - CMake调用底层构建工具（如make、ninja、msbuild等）
     - 编译源代码并链接目标
   - **常用选项**：

     - 指定构建配置：`cmake --build . --config Debug`（主要用于多配置生成器如Visual Studio）
     - 指定目标：`cmake --build . --target 目标名`（只构建特定目标）
     - 并行编译：`cmake --build . -j 线程数`（加速构建）
4. **运行程序**：

   ```bash
   # Linux/macOS
   ./hello_app

   # Windows
   .\hello_app.exe
   ```

### CMake变量作用域

- **基本规则**：

  - 变量默认在定义它的CMakeLists.txt文件及其子目录中可见
  - 子目录的变量不会自动向上传播到父目录
  - 使用 `set(变量名 值 PARENT_SCOPE)`可以将变量值传递给父作用域
- **常见变量类型**：

  - **普通变量**：使用 `set(VAR value)`定义，仅在当前作用域有效
  - **缓存变量**：使用 `set(VAR value CACHE STRING "描述")`定义，存储在CMakeCache.txt中，跨多次运行保持值
  - **环境变量**：使用 `set(ENV{VAR} value)`设置

### 常见问题和解决方案

1. **找不到头文件**：

   - **问题**：编译器报错找不到include的头文件
   - **解决**：使用 `target_include_directories(目标名 PRIVATE 包含目录)`添加头文件搜索路径
2. **CMake最低版本过高**：

   - **问题**：用户系统上的CMake版本低于要求
   - **解决**：降低所需的最低版本，或指导用户更新CMake
3. **编译器不支持指定的C++标准**：

   - **问题**：用户的编译器不支持要求的C++标准
   - **解决**：降低C++标准要求，或使用不同的编译器

## 示例2：库的使用与链接

### 目录结构

```
02_libraries/
├── CMakeLists.txt        # 主CMake构建脚本
├── include/
│   └── math_utils.h      # 数学工具库的头文件
└── src/
    ├── math_utils.cpp    # 数学工具库的实现
    └── main.cpp          # 使用库的主程序
```

### 源代码解析

**include/math_utils.h**:

```cpp
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

namespace math {
    int add(int a, int b);
    int subtract(int a, int b);
    double multiply(double a, double b);
    double divide(double a, double b);
}

#endif // MATH_UTILS_H
```

这个头文件定义了一个简单的数学工具命名空间，包含加、减、乘、除四个基础运算函数的声明。

**src/math_utils.cpp**:

```cpp
#include "math_utils.h"

namespace math {
    int add(int a, int b) {
        return a + b;
    }

    int subtract(int a, int b) {
        return a - b;
    }

    double multiply(double a, double b) {
        return a * b;
    }

    double divide(double a, double b) {
        return a / b;
    }
}
```

此文件实现了头文件中声明的四个数学函数。

**src/main.cpp**:

```cpp
#include <iostream>
#include "math_utils.h"

int main() {
    int a = 10, b = 5;
  
    std::cout << "数学运算示例：" << std::endl;
    std::cout << a << " + " << b << " = " << math::add(a, b) << std::endl;
    std::cout << a << " - " << b << " = " << math::subtract(a, b) << std::endl;
    std::cout << a << " * " << b << " = " << math::multiply(a, b) << std::endl;
    std::cout << a << " / " << b << " = " << math::divide(a, b) << std::endl;
  
    return 0;
}
```

这个主程序使用我们创建的数学工具库进行简单的四则运算并输出结果。

### CMakeLists.txt 详解

```cmake
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
```

#### 命令详解：

1. **add_library(math_utils STATIC src/math_utils.cpp)**

   - **作用**：创建一个名为 `math_utils`的静态库
   - **库类型**：
     - `STATIC`：静态库，在链接时被复制到可执行文件中
     - `SHARED`：动态/共享库，在运行时加载
     - `MODULE`：动态加载的模块，不会被链接，通常用于插件
   - **源文件**：这里只有一个源文件 `src/math_utils.cpp`
2. **target_include_directories(math_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)**

   - **作用**：为库目标指定头文件搜索路径
   - **目标**：第一个参数 `math_utils`是目标名称
   - **可见性修饰符**：
     - `PUBLIC`：此目录既用于编译此库，也会传递给链接此库的目标
     - `PRIVATE`：目录仅用于编译此库，不会传递
     - `INTERFACE`：目录不用于编译此库，但会传递给链接此库的目标
   - **路径**：`${CMAKE_CURRENT_SOURCE_DIR}/include`是包含目录的路径
     - `CMAKE_CURRENT_SOURCE_DIR`：当前处理的CMakeLists.txt所在目录
3. **target_link_libraries(math_app PRIVATE math_utils)**

   - **作用**：将库链接到可执行文件
   - **目标**：第一个参数 `math_app`是要链接库的目标
   - **可见性修饰符**：
     - `PRIVATE`：库仅用于此目标，不会传递依赖关系
     - `PUBLIC`：库用于此目标，并且传递给依赖此目标的其他目标
     - `INTERFACE`：库不用于此目标，但会传递给依赖此目标的其他目标
   - **库**：`math_utils`是要链接的库
4. **option(BUILD_SHARED_LIBRARY "构建共享库版本" OFF)**

   - **作用**：定义一个布尔选项，用户可在配置时修改
   - **参数**：
     - `BUILD_SHARED_LIBRARY`：选项名
     - `"构建共享库版本"`：选项描述
     - `OFF`：默认值（关闭）
5. **set_target_properties(math_utils_shared PROPERTIES ...)**

   - **作用**：为目标设置属性
   - **目标**：`math_utils_shared`是要设置属性的目标
   - **属性**：
     - `OUTPUT_NAME`：输出文件的实际名称（不带前缀/后缀）
     - `VERSION`：库的完整版本号（Linux上会生成如 `libmath_utils.so.1.0.0`）
     - `SOVERSION`：库的ABI版本号（兼容性版本号）

### 静态库与动态库的区别

1. **静态库（Static Library）**：

   - **文件扩展名**：`.a`（Linux/macOS）或 `.lib`（Windows）
   - **链接方式**：在编译时完全链接到可执行文件中
   - **优点**：
     - 部署简单，不需要额外的运行时依赖
     - 加载速度快，已在可执行文件中
   - **缺点**：
     - 增加可执行文件大小
     - 内存无法在多个进程间共享
     - 更新库需要重新编译所有使用它的应用
2. **动态库/共享库（Dynamic/Shared Library）**：

   - **文件扩展名**：`.so`（Linux）、`.dylib`（macOS）或 `.dll`（Windows）
   - **链接方式**：在运行时加载
   - **优点**：
     - 减小可执行文件大小
     - 内存可在多个进程间共享
     - 可以独立更新库，不需要重新编译应用
   - **缺点**：
     - 部署需要确保库文件可用
     - 可能引起版本兼容性问题
     - 加载时间稍长

### 依赖传递和可见性修饰符（PUBLIC/PRIVATE/INTERFACE）

理解这三个关键字至关重要，它们控制依赖关系如何传递：

假设有三个库：`A`、`B`和 `C`，其中 `A`依赖 `B`，`B`依赖 `C`。

1. **PRIVATE**：

   - `B`对 `C`的依赖是 `PRIVATE`时，`A`无法访问 `C`
   - `B`不会暴露任何关于 `C`的信息给 `A`
   - 示意图：`A` → `B` → `C`（`A`看不到 `C`）
   - 示例：
     ```cmake
     target_link_libraries(B PRIVATE C)
     target_include_directories(B PRIVATE C_headers)
     ```
2. **PUBLIC**：

   - `B`对 `C`的依赖是 `PUBLIC`时，`A`可以访问 `C`
   - `B`同时使用 `C`并将其暴露给 `A`
   - 示意图：`A` → `B` → `C`（`A`可以看到 `C`）
   - 示例：
     ```cmake
     target_link_libraries(B PUBLIC C)
     target_include_directories(B PUBLIC C_headers)
     ```
3. **INTERFACE**：

   - `B`对 `C`的依赖是 `INTERFACE`时，`A`可以访问 `C`，但 `B`自己不使用 `C`
   - `B`不使用 `C`，但要求任何使用 `B`的目标都必须使用 `C`
   - 示意图：`A` → `B` ---→ `C`（`B`不使用 `C`，但 `A`必须使用 `C`）
   - 示例：
     ```cmake
     target_link_libraries(B INTERFACE C)
     target_include_directories(B INTERFACE C_headers)
     ```

#### 如何选择正确的可见性修饰符

- **使用PRIVATE**：当依赖仅用于库的实现，与库的用户无关

  - 例如：用于库内部实现的辅助库、解析库内配置的XML解析器等
- **使用PUBLIC**：当依赖同时用于库的实现和接口

  - 例如：库的头文件中使用了某个依赖的类型或函数
- **使用INTERFACE**：当依赖仅在库的头文件中使用，不在实现中使用

  - 例如：纯模板库、仅在头文件中使用的依赖

### 构建和运行过程

1. **创建构建目录**：

   ```bash
   mkdir -p 02_libraries/build
   cd 02_libraries/build
   ```
2. **配置项目（默认构建静态库）**：

   ```bash
   cmake ..
   ```
3. **配置项目（构建静态库和共享库）**：

   ```bash
   cmake .. -DBUILD_SHARED_LIBRARY=ON
   ```
4. **构建项目**：

   ```bash
   cmake --build .
   ```
5. **运行程序**：

   ```bash
   # 静态库版本
   ./math_app

   # 共享库版本（如果启用）
   ./math_app_shared
   ```

### 库的命名约定

1. **Unix/Linux系统**：

   - **静态库**：`lib<name>.a`
     - 例如：`libmath_utils.a`
   - **共享库**：`lib<name>.so.<version>`
     - 例如：`libmath_utils.so.1.0.0`
     - 符号链接：`libmath_utils.so.1` → `libmath_utils.so.1.0.0`
     - 符号链接：`libmath_utils.so` → `libmath_utils.so.1`
2. **macOS系统**：

   - **静态库**：`lib<name>.a`
     - 例如：`libmath_utils.a`
   - **共享库**：`lib<name>.<version>.dylib`
     - 例如：`libmath_utils.1.0.0.dylib`
     - 符号链接：`libmath_utils.1.dylib` → `libmath_utils.1.0.0.dylib`
     - 符号链接：`libmath_utils.dylib` → `libmath_utils.1.dylib`
3. **Windows系统**：

   - **静态库**：`<name>.lib`
     - 例如：`math_utils.lib`
   - **共享库**：`<name>.dll` + `<name>.lib`（导入库）
     - 例如：`math_utils.dll` 和 `math_utils.lib`

### 常见问题和解决方案

1. **运行时找不到共享库**：

   - **问题**：程序启动时报错找不到共享库
   - **解决方案**：
     - **Linux/macOS**：设置 `LD_LIBRARY_PATH`（Linux）或 `DYLD_LIBRARY_PATH`（macOS）
       ```bash
       export LD_LIBRARY_PATH=/path/to/libs:$LD_LIBRARY_PATH
       ```
     - **Windows**：将DLL放在可执行文件同目录，或添加DLL目录到PATH
     - **更好的方法**：在CMake中设置可执行文件的RPATH
       ```cmake
       set_target_properties(math_app_shared PROPERTIES
           INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib"
       )
       ```
2. **链接错误**：

   - **问题**：编译成功但链接失败，找不到符号
   - **解决方案**：
     - 确保正确链接了所有依赖库
     - 检查库的依赖关系是否正确（PUBLIC/PRIVATE/INTERFACE）
     - 检查库是否正确导出符号（共享库可能需要特定的导出宏）
3. **静态库和共享库混合使用**：

   - **问题**：静态库链接到共享库可能导致多次初始化等问题
   - **解决方案**：
     - 静态库编译时添加位置无关代码选项（-fPIC）
       ```cmake
       set_target_properties(math_utils PROPERTIES
           POSITION_INDEPENDENT_CODE ON
       )
       ```

## 示例3：子目录与项目结构

### 目录结构

```
03_subdirectories/
├── CMakeLists.txt        # 顶层CMake构建脚本
├── app/
│   ├── CMakeLists.txt    # app子目录的CMake构建脚本
│   └── main.cpp          # 主程序源文件
└── lib/
    ├── CMakeLists.txt    # lib子目录的CMake构建脚本
    ├── include/
    │   └── calculator.h  # 计算器类的头文件
    └── src/
        └── calculator.cpp # 计算器类的实现
```

这个示例展示了一个更加复杂的项目结构，它包含多个子目录，每个子目录都有自己的CMakeLists.txt文件。这种结构适合于有明确模块划分的大型项目。

### 源代码解析

**lib/include/calculator.h**:

```cpp
#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
public:
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
};

#endif // CALCULATOR_H
```

定义了一个简单的`Calculator`类，包含四个基本算术运算的方法。

**lib/src/calculator.cpp**:

```cpp
#include "calculator.h"

double Calculator::add(double a, double b) {
    return a + b;
}

double Calculator::subtract(double a, double b) {
    return a - b;
}

double Calculator::multiply(double a, double b) {
    return a * b;
}

double Calculator::divide(double a, double b) {
    return a / b;
}
```

实现了`Calculator`类中声明的四个算术运算方法。

**app/main.cpp**:

```cpp
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
```

这是主程序，创建`Calculator`对象并演示其功能。

### CMakeLists.txt 详解

**顶层 CMakeLists.txt**:

```cmake
cmake_minimum_required(VERSION 3.10)
project(SubdirExample VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加子目录
add_subdirectory(lib)
add_subdirectory(app)

# 演示如何增加选项
option(BUILD_DOCS "构建文档" OFF)

if(BUILD_DOCS)
    message(STATUS "将生成文档")
    # 这里可以添加文档生成的相关命令
endif()
```

**lib/CMakeLists.txt**:

```cmake
# 创建库
add_library(calculator
    src/calculator.cpp
)

# 为库指定包含目录
target_include_directories(calculator
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
```

**app/CMakeLists.txt**:

```cmake
# 创建可执行文件
add_executable(calc_app main.cpp)

# 链接库
target_link_libraries(calc_app
    PRIVATE
        calculator
)
```

#### 命令详解：

1. **add_subdirectory(lib)**
   - **作用**：将子目录添加到构建中
   - **过程**：CMake会处理该子目录中的CMakeLists.txt文件
   - **执行顺序**：先处理顶层CMakeLists.txt中`add_subdirectory`之前的命令，然后处理子目录的CMakeLists.txt，最后回到顶层继续处理
   - **参数**：
     - `lib`：子目录的路径（相对于当前CMakeLists.txt所在目录）
     - 可选的第二个参数：指定子目录的构建输出目录
     - 可选的`EXCLUDE_FROM_ALL`参数：表示子目录中的目标默认不会被构建，除非显式指定

2. **变量作用域**：
   - 顶层CMakeLists.txt中设置的变量（如`CMAKE_CXX_STANDARD`）会被子目录继承
   - 子目录中设置的变量默认不会传递给父目录
   - 子目录中可以通过`set(变量名 值 PARENT_SCOPE)`将变量值传递给父目录

3. **目标可见性**：
   - 在子目录中定义的目标（如`calculator`库）在其他子目录中可见
   - 这使得`app`子目录可以直接使用`lib`子目录中定义的`calculator`库
   - 无需使用`PUBLIC/PRIVATE/INTERFACE`修饰符来控制目标的可见性

### 多目录项目的组织策略

#### 1. 按功能模块划分

将代码按照功能模块划分到不同目录：

```
project/
├── CMakeLists.txt
├── module1/
│   ├── CMakeLists.txt
│   ├── include/
│   └── src/
├── module2/
│   ├── CMakeLists.txt
│   ├── include/
│   └── src/
└── app/
    ├── CMakeLists.txt
    └── src/
```

#### 2. 按代码类型划分

将代码按类型（库、可执行文件、测试等）划分：

```
project/
├── CMakeLists.txt
├── libs/
│   ├── CMakeLists.txt
│   ├── lib1/
│   └── lib2/
├── apps/
│   ├── CMakeLists.txt
│   ├── app1/
│   └── app2/
└── tests/
    ├── CMakeLists.txt
    └── ...
```

#### 3. 按层次结构划分

将代码按照依赖层次划分：

```
project/
├── CMakeLists.txt
├── base/          # 基础层，不依赖其他模块
│   ├── CMakeLists.txt
│   └── ...
├── common/        # 通用层，依赖基础层
│   ├── CMakeLists.txt
│   └── ...
└── features/      # 功能层，依赖基础层和通用层
    ├── CMakeLists.txt
    └── ...
```

### 构建和运行过程

1. **创建构建目录**：
   ```bash
   mkdir -p 03_subdirectories/build
   cd 03_subdirectories/build
   ```

2. **配置项目**：
   ```bash
   cmake ..
   ```

3. **构建项目**：
   ```bash
   cmake --build .
   ```

4. **运行程序**：
   ```bash
   ./app/calc_app  # Linux/macOS
   .\app\calc_app.exe  # Windows
   ```

### 多子目录项目的优点

1. **模块化**：
   - 将代码分解为功能明确的模块
   - 每个模块有自己的CMakeLists.txt，可独立配置

2. **可重用性**：
   - 模块可以被多个项目或应用程序重用
   - 可以将常用模块打包为独立库

3. **依赖管理**：
   - 清晰表达模块间的依赖关系
   - 避免意外引入不必要的依赖

4. **并行开发**：
   - 多人开发时可以并行处理不同模块
   - 减少代码合并冲突

5. **选择性构建**：
   - 可以选择性地构建特定模块或组件
   - 使用`BUILD_模块名`类型的选项控制是否构建某个模块

### 常见问题和解决方案

1. **找不到子目录中定义的目标**：
   - **问题**：一个子目录无法找到另一个子目录中定义的目标
   - **解决方案**：
     - 确保目标所在的子目录已通过`add_subdirectory`添加
     - 检查子目录的添加顺序（被依赖的子目录应该先添加）
     - 使用`target_link_libraries`显式声明依赖关系

2. **重复定义变量**：
   - **问题**：子目录中重新定义了父目录中的变量，导致行为不一致
   - **解决方案**：
     - 使用条件检查避免重复设置：`if(NOT DEFINED 变量名)`
     - 使用更特定的变量名，加入模块前缀
     - 对于需要覆盖的变量，使用`CACHE`变量并设置`FORCE`选项

3. **构建产物位置不明确**：
   - **问题**：不清楚构建后的库和可执行文件位于何处
   - **解决方案**：
     - 使用`set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)`统一可执行文件输出位置
     - 使用`set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)`统一库文件输出位置
     - 使用`message()`命令输出关键路径信息

4. **多级子目录的包含路径问题**：
   - **问题**：深层子目录中的代码无法找到顶层或其他子目录中的头文件
   - **解决方案**：
     - 在顶层CMakeLists.txt中设置全局包含目录
     - 使用`PUBLIC`修饰符正确传递包含目录
     - 使用相对路径的包含语句：`#include "module/header.h"`而非`#include "header.h"`

### 最佳实践

1. **保持每个子目录的CMakeLists.txt简洁**：
   - 每个CMakeLists.txt关注自己的功能，不处理不相关的事情
   - 将公共设置放在顶层CMakeLists.txt中

2. **使用变量避免硬编码路径**：
   - 使用`${CMAKE_CURRENT_SOURCE_DIR}`指代当前目录
   - 使用`${CMAKE_CURRENT_BINARY_DIR}`指代当前构建目录

3. **不要在子目录中修改全局设置**：
   - 避免在子目录中修改`CMAKE_CXX_FLAGS`等全局变量
   - 使用`target_compile_options`等目标特定命令

4. **控制目标和变量的可见性**：
   - 合理使用`PUBLIC/PRIVATE/INTERFACE`修饰符
   - 使用`PARENT_SCOPE`明确表达变量传递的意图

5. **按照依赖关系顺序添加子目录**：
   - 被依赖的子目录应该先被添加
   - 例如：如果`app`依赖`lib`，则应先添加`lib`再添加`app`

## 示例4：选项、安装与测试

详细解析将在后续添加...

## 示例5：查找和使用第三方库

详细解析将在后续添加...

## 示例6：生成器表达式和自定义命令

详细解析将在后续添加...
