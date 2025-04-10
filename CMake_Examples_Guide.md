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

### 目录结构

```
04_options_install_test/
├── CMakeLists.txt            # 主CMake构建脚本
├── src/
│   ├── string_utils.h        # 字符串工具类的头文件
│   ├── string_utils.cpp      # 字符串工具类的实现
│   └── main.cpp              # 主程序
└── tests/
    ├── CMakeLists.txt        # 测试相关的CMake构建脚本
    └── test_string_utils.cpp # 测试程序
```

这个示例演示了三个重要的CMake功能：选项（让用户可以控制构建过程）、安装规则（定义如何安装项目）和测试集成（添加和运行测试）。

### 源代码解析

**src/string_utils.h**:

```cpp
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>

namespace utils {
    std::string to_upper(const std::string& str);
    std::string to_lower(const std::string& str);
    std::string reverse(const std::string& str);
    bool is_palindrome(const std::string& str);
}

#endif // STRING_UTILS_H
```

定义了一个字符串工具命名空间，包含大小写转换、字符串反转和回文检测功能。

**src/string_utils.cpp**:

```cpp
#include "string_utils.h"
#include <algorithm>
#include <cctype>

namespace utils {
    std::string to_upper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
                      [](unsigned char c){ return std::toupper(c); });
        return result;
    }
    
    std::string to_lower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
                      [](unsigned char c){ return std::tolower(c); });
        return result;
    }
    
    std::string reverse(const std::string& str) {
        std::string result = str;
        std::reverse(result.begin(), result.end());
        return result;
    }
    
    bool is_palindrome(const std::string& str) {
        std::string clean_str;
        // 移除非字母数字字符并转换为小写
        for (char c : str) {
            if (std::isalnum(c)) {
                clean_str.push_back(std::tolower(c));
            }
        }
        
        std::string reversed = clean_str;
        std::reverse(reversed.begin(), reversed.end());
        
        return clean_str == reversed;
    }
}
```

实现了头文件中声明的四个字符串工具函数。

**src/main.cpp**:

```cpp
#include <iostream>
#include "string_utils.h"

int main() {
    std::string input;
    
    std::cout << "Please enter a string: ";
    std::getline(std::cin, input);
    
    std::cout << "Uppercase: " << utils::to_upper(input) << std::endl;
    std::cout << "Lowercase: " << utils::to_lower(input) << std::endl;
    std::cout << "Reversed: " << utils::reverse(input) << std::endl;
    
    if (utils::is_palindrome(input)) {
        std::cout << "This is a palindrome!" << std::endl;
    } else {
        std::cout << "This is not a palindrome." << std::endl;
    }
    
    return 0;
}
```

主程序，用于演示字符串工具类的功能。

**tests/test_string_utils.cpp**:

```cpp
#include <iostream>
#include <cassert>
#include <string>
#include "../src/string_utils.h"

void test_to_upper() {
    assert(utils::to_upper("hello") == "HELLO");
    assert(utils::to_upper("Hello World") == "HELLO WORLD");
    assert(utils::to_upper("123") == "123");
    std::cout << "to_upper tests passed" << std::endl;
}

void test_to_lower() {
    assert(utils::to_lower("HELLO") == "hello");
    assert(utils::to_lower("Hello World") == "hello world");
    assert(utils::to_lower("123") == "123");
    std::cout << "to_lower tests passed" << std::endl;
}

void test_reverse() {
    assert(utils::reverse("hello") == "olleh");
    assert(utils::reverse("Hello World") == "dlroW olleH");
    assert(utils::reverse("12345") == "54321");
    std::cout << "reverse tests passed" << std::endl;
}

void test_is_palindrome() {
    assert(utils::is_palindrome("level") == true);
    assert(utils::is_palindrome("A man, a plan, a canal: Panama") == true);
    assert(utils::is_palindrome("hello") == false);
    std::cout << "is_palindrome tests passed" << std::endl;
}

int main() {
    test_to_upper();
    test_to_lower();
    test_reverse();
    test_is_palindrome();
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
```

测试程序，使用断言测试字符串工具类的每个功能。

### CMakeLists.txt 详解

**顶层 CMakeLists.txt**:

```cmake
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
```

**tests/CMakeLists.txt**:

```cmake
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
```

#### 命令详解：

1. **option(BUILD_TESTS "构建测试" ON)**
   - **作用**：定义一个布尔选项，让用户控制是否构建测试
   - **参数**：
     - `BUILD_TESTS`：选项名，在CMake中使用此变量名来检查选项状态
     - `"构建测试"`：选项描述，说明此选项的用途
     - `ON`：默认值，这里默认启用测试
   - **使用方式**：
     - 命令行中使用：`cmake .. -DBUILD_TESTS=OFF`（关闭测试构建）
     - 在CMake脚本中检查：`if(BUILD_TESTS) ... endif()`

2. **install命令**：
   - **作用**：定义安装规则，指定构建产物应该安装到哪里
   - **常见格式**：
     ```cmake
     install(TARGETS <目标1> [<目标2> ...]
         RUNTIME DESTINATION <可执行文件安装目录>
         LIBRARY DESTINATION <动态库安装目录>
         ARCHIVE DESTINATION <静态库安装目录>
     )
     ```
   - **DESTINATION参数**：
     - 指定安装目标的路径，可以是相对路径或绝对路径
     - 相对路径是相对于`CMAKE_INSTALL_PREFIX`变量
   - **常见的安装类型**：
     - `TARGETS`：安装目标（可执行文件、库）
     - `FILES`：安装单个文件
     - `DIRECTORY`：安装整个目录内容

3. **enable_testing()**
   - **作用**：启用对当前目录及其子目录的测试支持
   - **效果**：允许使用`add_test`命令添加测试，并且可以通过`ctest`命令运行测试

4. **add_test(NAME StringUtilsTest COMMAND test_string_utils)**
   - **作用**：添加一个测试用例
   - **参数**：
     - `NAME`：测试的名称，在运行`ctest`时可用来选择或排除特定测试
     - `COMMAND`：运行测试的命令，通常是之前构建的测试可执行文件
   - **额外选项**：
     - `WORKING_DIRECTORY`：指定测试运行的工作目录
     - `CONFIGURATIONS`：指定测试适用的构建配置（如Debug/Release）

5. **CMAKE_INSTALL_PREFIX**
   - **作用**：指定安装目标的根目录
   - **默认值**：
     - Unix系统：`/usr/local`
     - Windows系统：`C:/Program Files/<项目名>`
   - **自定义方式**：
     - 命令行：`cmake .. -DCMAKE_INSTALL_PREFIX=/opt/myapp`
     - CMake脚本：`set(CMAKE_INSTALL_PREFIX "/opt/myapp" CACHE PATH "..." FORCE)`

### 构建、测试和安装过程

1. **创建构建目录**：
   ```bash
   mkdir -p 04_options_install_test/build
   cd 04_options_install_test/build
   ```

2. **配置项目**：
   ```bash
   # 使用默认选项（开启测试）
   cmake ..
   
   # 或者，禁用测试
   cmake .. -DBUILD_TESTS=OFF
   
   # 自定义安装路径
   cmake .. -DCMAKE_INSTALL_PREFIX=~/myapps
   ```

3. **构建项目**：
   ```bash
   cmake --build .
   ```

4. **运行测试**：
   ```bash
   # 运行所有测试
   ctest
   
   # 运行特定测试
   ctest -R StringUtilsTest
   
   # 详细模式运行测试
   ctest -V
   ```

5. **安装项目**：
   ```bash
   # 使用默认安装路径
   cmake --install .
   
   # 或覆盖安装路径
   cmake --install . --prefix ~/myapps
   ```

### 选项、安装与测试的最佳实践

#### 选项最佳实践

1. **提供合理的默认值**：
   - 选择对大多数用户最合适的默认值
   - 对于可选功能，通常默认为`OFF`
   - 对于基本功能，通常默认为`ON`

2. **使用描述性的选项名称**：
   - 使用`BUILD_`前缀表示构建选项
   - 使用`ENABLE_`前缀表示启用功能
   - 使用`WITH_`前缀表示可选依赖

3. **分组相关选项**：
   - 在CMakeLists.txt中将相关选项放在一起
   - 可以使用注释分隔不同类别的选项

4. **使选项的依赖关系明确**：
   ```cmake
   option(WITH_FEATURE_A "Enable Feature A" ON)
   option(WITH_FEATURE_B "Enable Feature B (requires A)" OFF)
   
   if(WITH_FEATURE_B AND NOT WITH_FEATURE_A)
       message(WARNING "Feature B requires Feature A, enabling Feature A")
       set(WITH_FEATURE_A ON CACHE BOOL "Enable Feature A" FORCE)
   endif()
   ```

#### 安装规则最佳实践

1. **遵循标准目录结构**：
   - 可执行文件安装到`bin`目录
   - 库文件安装到`lib`目录
   - 头文件安装到`include`目录
   - 文档安装到`doc`或`share/doc`目录
   - 配置文件安装到`etc`目录

2. **使用相对路径**：
   - 使用相对于`CMAKE_INSTALL_PREFIX`的安装路径
   - 避免硬编码绝对路径

3. **安装必要的运行时依赖**：
   - 确保安装所有运行所需的库和资源文件
   - 对于共享库，设置正确的RPATH

4. **提供卸载支持**：
   ```cmake
   # 添加卸载目标
   if(NOT TARGET uninstall)
       configure_file(
           "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
           "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
           @ONLY)
       add_custom_target(uninstall
           COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
   endif()
   ```

#### 测试最佳实践

1. **组织测试**：
   - 为每个组件或模块创建单独的测试
   - 使用描述性的测试名称

2. **使用有意义的断言**：
   - 每个测试应专注于一个方面或功能
   - 断言失败时提供有用的错误信息

3. **测试覆盖率**：
   - 尽量覆盖所有代码路径
   - 包括边界条件和错误处理

4. **集成到CI系统**：
   - 使测试成为持续集成流程的一部分
   - 添加`test`目标到构建系统

### 常见问题和解决方案

1. **安装权限问题**：
   - **问题**：安装到系统目录需要管理员权限
   - **解决方案**：
     - 使用自定义安装前缀：`cmake -DCMAKE_INSTALL_PREFIX=$HOME/local ..`
     - 或使用`sudo`运行安装命令：`sudo cmake --install .`

2. **测试找不到依赖库**：
   - **问题**：测试可执行文件在运行时找不到动态库
   - **解决方案**：
     - 设置RPATH：`set_target_properties(test_exe PROPERTIES INSTALL_RPATH "\${ORIGIN}/../lib")`
     - 或设置环境变量：`LD_LIBRARY_PATH=./lib ctest`

3. **选项之间的依赖关系**：
   - **问题**：某些选项依赖于其他选项，但用户可能不知道
   - **解决方案**：
     - 检查并自动启用依赖项
     - 或在禁用被依赖选项时发出警告

4. **安装后程序无法运行**：
   - **问题**：安装后的程序找不到动态库或资源文件
   - **解决方案**：
     - 正确设置安装RPATH
     - 安装所有必要的依赖库
     - 使用相对路径访问资源文件

## 示例5：查找和使用第三方库

### 目录结构

```
05_find_package/
├── CMakeLists.txt        # 主CMake构建脚本
└── main.cpp              # 使用外部库的程序
```

这个示例演示如何在CMake项目中查找和使用外部第三方库，这是实际项目开发中的常见需求。

### 源代码解析

**main.cpp**:

```cpp
#include <iostream>
#include <filesystem>
#include <boost/algorithm/string.hpp>

int main() {
    // 使用Boost库
    std::string str = "Hello, World!";
    std::cout << "Original string: " << str << std::endl;
    
    boost::to_upper(str);
    std::cout << "After Boost processing: " << str << std::endl;
    
    // 使用C++17 filesystem
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::cout << "Current path: " << currentPath << std::endl;
    
    return 0;
}
```

这个程序展示了如何使用两个外部依赖：
1. **Boost库**的字符串算法，用于将字符串转换为大写
2. **C++17的文件系统库**，用于获取当前路径

### CMakeLists.txt 详解

```cmake
cmake_minimum_required(VERSION 3.14)
project(FindPackageExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Boost库
find_package(Boost 1.65 REQUIRED COMPONENTS system filesystem)

# 检查是否找到Boost
if(Boost_FOUND)
    message(STATUS "Found Boost: ${Boost_VERSION}")
else()
    message(FATAL_ERROR "Required Boost library not found")
endif()

# 创建可执行文件
add_executable(boost_demo main.cpp)

# 链接Boost库
target_link_libraries(boost_demo
    PRIVATE
        Boost::system
        Boost::filesystem
)

# 如果使用的是GCC或Clang，需要链接 stdc++fs 来支持std::filesystem
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_link_libraries(boost_demo PRIVATE stdc++fs)
endif()

# 打印Boost库的信息
message(STATUS "Boost include directories: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost library directories: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
```

#### 命令详解：

1. **find_package(Boost 1.65 REQUIRED COMPONENTS system filesystem)**
   - **作用**：查找Boost库及其组件
   - **参数**：
     - `Boost`：要查找的包名称
     - `1.65`：最低需要的版本号
     - `REQUIRED`：表示此库是必须的，如果未找到则停止配置
     - `COMPONENTS`：指定需要的特定组件
     - `system filesystem`：需要的Boost组件名称
   - **查找机制**：
     - CMake会在预定义的路径和CMAKE_PREFIX_PATH中搜索Boost
     - 会查找名为`FindBoost.cmake`(模块模式)或`BoostConfig.cmake`/`boost-config.cmake`(配置模式)的文件
   - **成功后设置的变量**：
     - `Boost_FOUND`：布尔值，表示是否找到Boost
     - `Boost_INCLUDE_DIRS`：Boost头文件目录
     - `Boost_LIBRARY_DIRS`：Boost库文件目录
     - `Boost_LIBRARIES`：要链接的Boost库列表

2. **target_link_libraries(boost_demo PRIVATE Boost::system Boost::filesystem)**
   - **作用**：将Boost库链接到目标
   - **现代用法**：
     - 使用`Boost::`为前缀的导入目标(imported targets)
     - 这些目标由`find_package(Boost)`创建
     - 比使用变量如`${Boost_LIBRARIES}`更干净和可靠
   - **旧式用法**(不推荐)：
     ```cmake
     include_directories(${Boost_INCLUDE_DIRS})
     link_directories(${Boost_LIBRARY_DIRS})
     target_link_libraries(boost_demo ${Boost_LIBRARIES})
     ```

### find_package的两种模式

CMake的`find_package`命令有两种操作模式，理解这两种模式对于正确使用第三方库至关重要：

1. **模块模式（Module Mode）**：
   - **查找过程**：
     - 查找名为`Find<PackageName>.cmake`的文件
     - 在`CMAKE_MODULE_PATH`和CMake安装的模块目录中查找
   - **特点**：
     - 通常由CMake提供或项目自定义
     - 一般设置`<PackageName>_FOUND`, `<PackageName>_INCLUDE_DIRS`, `<PackageName>_LIBRARIES`等变量
   - **例子**：`FindBoost.cmake`, `FindZLIB.cmake`

2. **配置模式（Config Mode）**：
   - **查找过程**：
     - 查找名为`<PackageName>Config.cmake`或`<lowercase-packagename>-config.cmake`的文件
     - 在多个标准位置查找，如`<prefix>/lib/cmake/<PackageName>/`
   - **特点**：
     - 通常由软件包本身提供
     - 一般创建导入目标(imported targets)
     - 现代CMake推荐的方式
   - **例子**：`Qt5Config.cmake`, `OpenCVConfig.cmake`

### 常用第三方库的查找方式

#### 1. Boost

```cmake
# 现代方式
find_package(Boost 1.65 REQUIRED COMPONENTS system filesystem)
target_link_libraries(myapp PRIVATE Boost::system Boost::filesystem)

# 如果找不到，可以提供提示
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found. Please install Boost or set BOOST_ROOT.")
endif()
```

#### 2. OpenSSL

```cmake
find_package(OpenSSL REQUIRED)
target_link_libraries(myapp PRIVATE OpenSSL::SSL OpenSSL::Crypto)
```

#### 3. Qt

```cmake
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
target_link_libraries(myapp PRIVATE Qt5::Core Qt5::Widgets)
```

#### 4. OpenCV

```cmake
find_package(OpenCV REQUIRED)
target_link_libraries(myapp PRIVATE ${OpenCV_LIBS})
```

#### 5. 自定义位置的库

```cmake
# 设置搜索路径提示
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "D:/libraries/mylib")
find_package(MyLib REQUIRED)
```

### 创建和使用自己的Find模块

如果需要使用的库没有CMake支持，可以创建自己的Find模块：

1. **创建`FindMyLib.cmake`文件**：

```cmake
# FindMyLib.cmake
# 定义查找变量
find_path(MyLib_INCLUDE_DIR mylib.h
    HINTS
        ${MyLib_ROOT}/include
        $ENV{MyLib_ROOT}/include
    PATHS
        /usr/include
        /usr/local/include
)

find_library(MyLib_LIBRARY
    NAMES mylib libmylib
    HINTS
        ${MyLib_ROOT}/lib
        $ENV{MyLib_ROOT}/lib
    PATHS
        /usr/lib
        /usr/local/lib
)

# 处理REQUIRED和QUIET参数
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MyLib
    REQUIRED_VARS MyLib_LIBRARY MyLib_INCLUDE_DIR
)

# 设置输出变量
if(MyLib_FOUND)
    set(MyLib_LIBRARIES ${MyLib_LIBRARY})
    set(MyLib_INCLUDE_DIRS ${MyLib_INCLUDE_DIR})
    
    # 创建导入目标
    if(NOT TARGET MyLib::MyLib)
        add_library(MyLib::MyLib UNKNOWN IMPORTED)
        set_target_properties(MyLib::MyLib PROPERTIES
            IMPORTED_LOCATION "${MyLib_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${MyLib_INCLUDE_DIR}"
        )
    endif()
endif()

# 标记高级变量
mark_as_advanced(MyLib_INCLUDE_DIR MyLib_LIBRARY)
```

2. **使用自定义Find模块**：

```cmake
# 将模块目录添加到搜索路径
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# 查找库
find_package(MyLib REQUIRED)

# 使用库
target_link_libraries(myapp PRIVATE MyLib::MyLib)
```

### 构建和运行过程

1. **安装依赖**：
   - 首先确保安装了Boost库（版本1.65或更高）
   - 在Linux上：`sudo apt-get install libboost-all-dev`
   - 在macOS上：`brew install boost`
   - 在Windows上：从官网下载并安装，或使用vcpkg/Chocolatey

2. **创建构建目录**：
   ```bash
   mkdir -p 05_find_package/build
   cd 05_find_package/build
   ```

3. **配置项目**：
   ```bash
   # 使用系统默认位置的Boost
   cmake ..
   
   # 或者指定Boost位置
   cmake .. -DBOOST_ROOT=/path/to/boost
   ```

4. **构建项目**：
   ```bash
   cmake --build .
   ```

5. **运行程序**：
   ```bash
   ./boost_demo
   ```

### 高级find_package技巧

#### 1. 使用组件查找

```cmake
# 只查找需要的组件
find_package(Boost COMPONENTS filesystem system REQUIRED)
```

#### 2. 指定版本范围

```cmake
# 版本必须在1.65到1.70之间
find_package(Boost 1.65...1.70 REQUIRED)
```

#### 3. 查找多个包

```cmake
# 查找多个包，同时处理失败情况
include(CMakeDependentOption)
find_package(OpenSSL)
cmake_dependent_option(WITH_SSL "Enable SSL support" ON "OpenSSL_FOUND" OFF)
```

#### 4. 提供备选方案

```cmake
# 尝试查找LibA，如果没找到则查找LibB
find_package(LibA QUIET)
if(NOT LibA_FOUND)
    find_package(LibB REQUIRED)
    set(USE_LIBB TRUE)
endif()
```

#### 5. 使用CONFIG模式

```cmake
# 明确使用CONFIG模式
find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Widgets)
```

### 常见问题和解决方案

1. **找不到库**：
   - **问题**：`find_package`无法找到安装的库
   - **解决方案**：
     - 设置`<PackageName>_ROOT`变量：`-DBoost_ROOT=/path/to/boost`
     - 设置`CMAKE_PREFIX_PATH`：`-DCMAKE_PREFIX_PATH=/path/to/libraries`
     - 检查库是否确实安装在标准位置
     - 在Windows上，可能需要设置`<PackageName>_DIR`指向包含Config文件的目录

2. **版本不匹配**：
   - **问题**：找到的库版本低于需求
   - **解决方案**：
     - 安装更新版本的库
     - 如果无法更新，考虑降低版本要求
     - 检查是否有多个版本的库同时安装，CMake可能找到旧版本

3. **链接错误**：
   - **问题**：找到库但链接时报错未定义符号
   - **解决方案**：
     - 确保链接了正确的组件/库
     - 检查是否需要链接额外的依赖库
     - 检查库的ABI兼容性（如Debug/Release混合使用）

4. **导入目标与变量选择**：
   - **问题**：不确定是使用导入目标还是变量
   - **解决方案**：
     - 优先使用导入目标（如`Boost::filesystem`）
     - 如果不存在导入目标，则使用变量（如`${Boost_LIBRARIES}`）
     - 可以检查是否定义了导入目标：`if(TARGET Boost::filesystem)`

5. **查找特定版本**：
   - **问题**：需要特定版本的库
   - **解决方案**：
     - 指定版本号：`find_package(Boost 1.65 EXACT)`
     - 设置版本策略变量：`set(Boost_EXACT ON)`
     - 如有多个版本，可以指定完整路径

## 示例6：生成器表达式和自定义命令

### 目录结构

```
06_advanced/
├── CMakeLists.txt        # 主CMake构建脚本
├── src/
│   ├── main.cpp          # 主程序
│   └── config.h.in       # 配置头文件模板
```

这个示例演示了CMake的两个高级功能：生成器表达式和自定义命令。这些功能可以大大增强CMake项目的灵活性和功能性。

### 源代码解析

**src/config.h.in**:

```cpp
#ifndef CONFIG_H
#define CONFIG_H

#define PROJECT_NAME "@PROJECT_NAME@"
#define PROJECT_VERSION "@PROJECT_VERSION@"
#define PROJECT_VERSION_MAJOR @PROJECT_VERSION_MAJOR@
#define PROJECT_VERSION_MINOR @PROJECT_VERSION_MINOR@

#endif // CONFIG_H
```

这是一个配置头文件模板，使用`@变量名@`语法引用CMake变量，在配置阶段会被实际值替换。

**src/main.cpp**:

```cpp
#include <iostream>
#include "config.h"

int main() {
    std::cout << "Project name: " << PROJECT_NAME << std::endl;
    std::cout << "Project version: " << PROJECT_VERSION << std::endl;
    std::cout << "Major version: " << PROJECT_VERSION_MAJOR << std::endl;
    std::cout << "Minor version: " << PROJECT_VERSION_MINOR << std::endl;
    
#ifdef DEBUG_BUILD
    std::cout << "This is a debug build" << std::endl;
#else
    std::cout << "This is a release build" << std::endl;
#endif
    
    return 0;
}
```

这个程序使用了通过配置生成的头文件，并展示了如何根据构建类型输出不同的信息。

### CMakeLists.txt 详解

```cmake
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
    COMMAND ${CMAKE_COMMAND} -E echo "Build completed: $<TARGET_FILE:advanced_app>"
    COMMENT "Displaying build information"
)

# 添加一个自定义目标
add_custom_target(run_app
    COMMAND advanced_app
    DEPENDS advanced_app
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running application"
)
```

#### 命令详解：

1. **configure_file(src/config.h.in ${CMAKE_BINARY_DIR}/generated/config.h)**
   - **作用**：根据模板生成配置文件
   - **过程**：
     - 读取源文件`src/config.h.in`
     - 将`@变量名@`替换为实际的CMake变量值
     - 将结果写入目标文件`${CMAKE_BINARY_DIR}/generated/config.h`
   - **常见用途**：
     - 将项目版本信息嵌入代码
     - 将构建路径嵌入代码
     - 根据CMake配置启用/禁用功能

2. **生成器表达式**
   - **语法**：`$<condition:true_text>`或`$<condition:true_text:false_text>`
   - **求值时机**：构建系统生成阶段而非配置阶段
   - **优势**：
     - 可以基于生成器本身的信息（如构建类型）进行条件处理
     - 支持复杂的条件逻辑，包括嵌套条件
   - **常见条件**：
     - `$<CONFIG:配置类型>`：如`$<CONFIG:Debug>`在Debug配置时为1
     - `$<PLATFORM_ID:标识>`：如`$<PLATFORM_ID:Windows>`
     - `$<CXX_COMPILER_ID:标识>`：如`$<CXX_COMPILER_ID:MSVC>`
     - `$<BOOL:值>`：如`$<BOOL:${变量}>`
     - `$<AND:条件1,条件2,...>`：当所有条件都为真时为1
     - `$<OR:条件1,条件2,...>`：当任一条件为真时为1
     - `$<NOT:条件>`：当条件为假时为1

3. **add_custom_command(TARGET advanced_app POST_BUILD ...)**
   - **作用**：向指定目标添加自定义命令
   - **时机**：
     - `PRE_BUILD`：在目标构建之前运行（仅适用于Visual Studio）
     - `PRE_LINK`：在编译后，链接前运行
     - `POST_BUILD`：在目标构建完成后运行
   - **命令**：
     - `COMMAND`：要执行的命令
     - `COMMENT`：执行命令时显示的消息
     - `WORKING_DIRECTORY`：命令执行的工作目录
     - `DEPENDS`：命令的其他依赖

4. **add_custom_target(run_app ...)**
   - **作用**：添加一个不产生输出的自定义目标
   - **用途**：
     - 定义额外的构建目标，如运行程序、生成文档
     - 用作其他目标的依赖项
     - 执行额外的构建步骤
   - **参数**：
     - `COMMAND`：运行目标时执行的命令
     - `DEPENDS`：目标的依赖
     - `WORKING_DIRECTORY`：命令执行的工作目录
     - `COMMENT`：执行命令时显示的消息
   - **使用方式**：
     - 通过`cmake --build . --target run_app`执行

### 生成器表达式详解

生成器表达式是CMake的强大功能，允许在生成构建系统时（而非配置时）计算值。以下是常见的生成器表达式类型和用法：

#### 1. 逻辑表达式

```cmake
# 如果是Debug配置，则为1，否则为0
$<CONFIG:Debug>

# 如果编译器是MSVC，则为1，否则为0
$<CXX_COMPILER_ID:MSVC>

# 逻辑与：A和B都为真时为1
$<AND:$<CONDITION_A>,$<CONDITION_B>>

# 逻辑或：A或B为真时为1
$<OR:$<CONDITION_A>,$<CONDITION_B>>

# 逻辑非：条件为假时为1
$<NOT:$<CONDITION>>
```

#### 2. 字符串操作表达式

```cmake
# 如果条件为真，返回真文本，否则返回空字符串
$<condition:true_text>

# 如果条件为真，返回真文本，否则返回假文本
$<IF:condition,true_text,false_text>

# 字符串连接
$<STREQUAL:string1,string2> # 如果string1等于string2，则为1，否则为0
```

#### 3. 路径表达式

```cmake
# 目标文件的完整路径
$<TARGET_FILE:target>

# 目标的输出名称（不含目录）
$<TARGET_FILE_NAME:target>

# 目标的链接库目录
$<TARGET_LINKER_FILE_DIR:target>
```

#### 4. 编译器和平台特定表达式

```cmake
# 如果目标平台是Windows，则为1
$<PLATFORM_ID:Windows>

# 如果是32位架构，则为1
$<EQUAL:${CMAKE_SIZEOF_VOID_P},4>

# 如果C++编译器支持C++14，则为1
$<COMPILE_FEATURES:cxx_std_14>
```

#### 5. 实际应用场景

```cmake
# 根据构建类型设置不同的编译选项
target_compile_options(myapp PRIVATE
    $<$<CONFIG:Debug>:-g -O0>
    $<$<CONFIG:Release>:-O3>
)

# 根据编译器设置不同的警告标志
target_compile_options(myapp PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Werror>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Werror>
)

# 条件包含目录
target_include_directories(myapp PRIVATE
    $<$<BOOL:${WITH_FEATURE}>:${FEATURE_INCLUDE_DIR}>
)

# 为共享库和静态库使用不同的定义
target_compile_definitions(mylib PRIVATE
    $<$<BOOL:${BUILD_SHARED_LIBS}>:MYLIB_EXPORTS>
)
```

### 自定义命令和目标详解

自定义命令和目标允许在构建过程中执行任意操作，极大地扩展了CMake的功能：

#### 1. 构建时代码生成

```cmake
# 使用工具生成源文件
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated_code.cpp
    COMMAND code_generator ${CMAKE_CURRENT_SOURCE_DIR}/spec.json
             -o ${CMAKE_CURRENT_BINARY_DIR}/generated_code.cpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/spec.json code_generator
    COMMENT "Generating source code from spec"
)

# 将生成的源文件添加到目标
add_executable(myapp main.cpp ${CMAKE_CURRENT_BINARY_DIR}/generated_code.cpp)
```

#### 2. 资源编译

```cmake
# 编译资源文件
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources.bin
    COMMAND resource_compiler ${CMAKE_CURRENT_SOURCE_DIR}/resources/
             -o ${CMAKE_CURRENT_BINARY_DIR}/resources.bin
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resources/*
    COMMENT "Compiling resources"
)

# 将编译的资源添加到目标
add_executable(myapp main.cpp)
add_dependencies(myapp ${CMAKE_CURRENT_BINARY_DIR}/resources.bin)
```

#### 3. 文档生成

```cmake
# 添加生成文档的目标
add_custom_target(docs
    COMMAND doxygen ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
)
```

#### 4. 自定义构建步骤

```cmake
# 添加后处理步骤
add_custom_command(
    TARGET myapp
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:myapp> ${CMAKE_CURRENT_BINARY_DIR}/dist/
    COMMAND ${CMAKE_COMMAND} -E echo "Copied executable to dist directory"
    COMMENT "Performing post-build step"
)
```

#### 5. 自定义安装步骤

```cmake
# 安装前创建目录
install(CODE "
    message(STATUS \"Creating directory: \${CMAKE_INSTALL_PREFIX}/data\")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory \${CMAKE_INSTALL_PREFIX}/data
    )
")

# 安装后运行脚本
install(CODE "
    message(STATUS \"Running post-install script\")
    execute_process(
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/scripts/post_install.sh
        WORKING_DIRECTORY \${CMAKE_INSTALL_PREFIX}
    )
")
```

### 构建和运行过程

1. **创建构建目录**：
   ```bash
   mkdir -p 06_advanced/build
   cd 06_advanced/build
   ```

2. **配置项目**：
   ```bash
   # 使用系统默认位置的Boost
   cmake ..
   
   # 或者指定Boost位置
   cmake .. -DBOOST_ROOT=/path/to/boost
   ```

3. **构建项目**：
   ```bash
   cmake --build .
   ```

4. **直接运行程序**：
   ```bash
   ./advanced_app
   ```

5. **通过自定义目标运行**：
   ```bash
   cmake --build . --target run_app
   ```

### 最佳实践

1. **生成器表达式**：
   - 避免过度复杂的表达式，保持可读性
   - 使用注释说明复杂表达式的目的
   - 优先使用现代CMake的目标属性而非全局变量

2. **自定义命令**：
   - 确保命令的输入和输出依赖正确声明
   - 对于复杂的命令，考虑使用CMake脚本文件
   - 使用`VERBATIM`选项确保命令正确转义

3. **自定义目标**：
   - 给目标起描述性名称，表明其用途
   - 使用`DEPENDS`确保正确的构建顺序
   - 考虑添加到`all`目标（默认行为）或从`all`排除（使用`EXCLUDE_FROM_ALL`）

4. **配置文件**：
   - 使用描述性变量名，避免冲突
   - 考虑使用`@ONLY`选项，只替换`@变量@`语法
   - 对于更复杂的替换，考虑使用`file(GENERATE)`

### 常见问题和解决方案

1. **生成器表达式不起作用**：
   - **问题**：生成器表达式似乎被忽略
   - **解决方案**：
     - 确保使用正确的语法
     - 确保表达式用在支持的命令中
     - 检查CMake版本是否支持该表达式
     - 使用`message(STATUS "Expr: $<...>")`不会显示结果，因为生成器表达式在生成时才求值

2. **自定义命令执行顺序问题**：
   - **问题**：自定义命令没有按预期顺序执行
   - **解决方案**：
     - 正确设置依赖关系
     - 理解`PRE_BUILD`、`PRE_LINK`和`POST_BUILD`的区别
     - 使用`add_dependencies`确保目标间的依赖关系

3. **路径问题**：
   - **问题**：自定义命令使用的路径不正确
   - **解决方案**：
     - 使用绝对路径：`${CMAKE_CURRENT_SOURCE_DIR}`、`${CMAKE_CURRENT_BINARY_DIR}`
     - 对于包含空格的路径，使用引号或转义
     - 使用CMake命令行工具：`${CMAKE_COMMAND} -E copy ...`

4. **平台兼容性问题**：
   - **问题**：自定义命令在不同平台行为不一致
   - **解决方案**：
     - 使用CMake内置命令：`${CMAKE_COMMAND} -E ...`
     - 基于平台使用不同的命令：`$<$<PLATFORM_ID:Windows>:命令1>$<$<NOT:$<PLATFORM_ID:Windows>>:命令2>`
     - 考虑使用CMake脚本处理复杂逻辑
