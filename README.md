# CMake 学习项目

这个仓库包含了一系列CMake示例，旨在帮助您从零开始学习CMake构建系统。示例由简单到复杂，覆盖了CMake的核心概念和常见用法，适合初学者逐步掌握CMake的各项功能。

> **注意**：本仓库内容主要由AI（Claude 3.7 Sonnet）根据学习计划自动生成，包括示例代码、CMakeLists.txt文件和文档。通过AI辅助创建的学习材料，旨在提供统一和全面的CMake学习体验。

## 项目结构

```
cmake_learning/
├── 01_basic/                     # 示例1：基础命令 - Hello World
├── 02_libraries/                 # 示例2：库的使用与链接
├── 03_subdirectories/            # 示例3：子目录与项目结构
├── 04_options_install_test/      # 示例4：选项、安装与测试
├── 05_find_package/              # 示例5：查找和使用第三方库
├── 06_advanced/                  # 示例6：生成器表达式和自定义命令
├── CMake_Examples_Guide.md       # 详细的示例解析文档
├── CMake_Learning_Schedule.md    # CMake学习计划
├── .gitignore                    # Git忽略文件配置
└── README.md                     # 本文件
```

## 示例内容

### 示例1：基础命令 - Hello World
最简单的CMake项目，演示基本命令和构建流程。包含一个简单的C++程序和基础的CMakeLists.txt文件。

### 示例2：库的使用与链接
展示如何创建和使用静态库和动态库，介绍库的链接和依赖关系传递。理解 `PUBLIC`、`PRIVATE` 和 `INTERFACE` 关键字的用法。

### 示例3：子目录与项目结构
演示如何组织多目录项目，使用子目录管理复杂项目结构。

### 示例4：选项、安装与测试
展示如何添加构建选项，定义安装规则，以及集成测试功能。

### 示例5：查找和使用第三方库
演示如何使用 `find_package` 查找和集成外部依赖库。

### 示例6：生成器表达式和自定义命令
介绍高级特性，如生成器表达式、自定义命令和目标。

## 环境要求

- CMake 3.10 或更高版本
- 支持C++11的编译器（GCC、Clang、MSVC等）
- 示例5需要安装Boost库（1.65或更高版本）

## 使用方法

每个示例都可以单独构建和运行，基本步骤如下：

### Linux/macOS/Windows

```bash
# 以示例1为例
cd 01_basic
mkdir build && cd build
cmake ..
cmake --build .
./hello_app  # Linux/macOS
.\hello_app.exe  # Windows
```

对于需要特殊选项的示例：

```bash
# 构建共享库版本（示例2）
cd 02_libraries
mkdir build && cd build
cmake .. -DBUILD_SHARED_LIBRARY=ON
cmake --build .
```

## 编码考虑

本项目代码默认使用英文避免编码问题，但如果您想在项目中使用非ASCII字符（如中文），请注意以下事项：

1. **源文件编码**：
   - 确保所有源文件使用UTF-8编码保存
   - 在大多数现代编辑器中，这是默认设置

2. **编译器选项**：
   - 对于MSVC编译器，可在CMakeLists.txt中添加以下选项支持UTF-8：
     ```cmake
     if(MSVC)
       add_compile_options(/utf-8)
     endif()
     ```
   - 对于GCC/Clang，可添加：
     ```cmake
     if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
       add_compile_options(-finput-charset=UTF-8)
     endif()
     ```

3. **控制台输出**：
   - Windows平台下可能需要设置控制台代码页以正确显示非ASCII字符：
     ```cpp
     #ifdef _WIN32
     #include <windows.h>
     SetConsoleOutputCP(CP_UTF8);
     #endif
     ```

## 学习建议

1. 按照示例顺序学习，每个示例都基于前面示例的知识
2. 对每个示例，先阅读 `CMake_Examples_Guide.md` 中的相关章节
3. 查看源代码和CMakeLists.txt文件，理解其结构和命令
4. 亲自构建和运行示例，尝试修改参数和选项
5. 参考 `cmakeLearning.md` 中的学习计划和资源链接

## 文档资源

- **CMake_Examples_Guide.md**：详细的示例解析，包含命令说明、概念解释和最佳实践
- **CMake_Learning_Schedule.md**：完整的CMake学习计划，包含核心概念和学习资源

## 贡献

欢迎提交问题和改进建议！如果您发现bug或有改进想法，请创建issue或提交pull request。

## 许可

本项目采用MIT许可证。详见LICENSE文件。 