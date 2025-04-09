# CMake 学习计划

## 1. CMake 简介与核心概念

*   **目标**: 理解 CMake 的作用和基本工作原理。
*   **内容**:
    *   CMake 是什么？ (跨平台构建系统生成器)
    *   为什么需要 CMake？ (解决不同平台、编译器、IDE 的构建差异)
    *   核心概念:
        *   `CMakeLists.txt`: CMake 的构建脚本文件。
        *   **Generator (生成器)**: CMake 根据 `CMakeLists.txt` 生成特定本地构建工具的文件 (如 Makefiles, Visual Studio solutions, Ninja files)。
        *   **Target (目标)**: 构建的产物，通常是可执行文件 (`executable`) 或库 (`library`)。
        *   **Command (命令)**: CMake 脚本中使用的函数，用于定义项目、目标、依赖关系等。
        *   **Variable (变量)**: 存储路径、选项、编译器标志等信息。
        *   **Build Types (构建类型)**: 如 `Debug`, `Release`, `RelWithDebInfo`, `MinSizeRel`，用于控制优化级别和调试信息。
    *   **常用工具**:
        *   `cmake`: 命令行工具，用于配置和生成构建系统。
        *   `cmake-gui`: 图形界面工具，用于配置选项。
        *   `ctest`: 用于运行 CMake 项目中定义的测试。
        *   `cpack`: 用于生成安装包。

## 2. 基础命令与构建流程 (入门)

*   **目标**: 能够使用 CMake 构建一个简单的 C++ 项目。
*   **学习顺序与命令**:

    1.  **`cmake_minimum_required(VERSION x.y)`**:
        *   **作用**: 指定运行此脚本所需的最低 CMake 版本。
        *   **位置**: 必须是 `CMakeLists.txt` 的第一条有效命令。
        *   **示例**: `cmake_minimum_required(VERSION 3.10)`

    2.  **`project(ProjectName [VERSION x.y.z] [LANGUAGES CXX C ...])`**:
        *   **作用**: 定义项目名称、可选版本和使用的编程语言 (如 C++ 是 `CXX`, C 是 `C`)。
        *   **效果**: 会自动定义一些有用的变量，如 `PROJECT_NAME`, `PROJECT_SOURCE_DIR` (项目根目录), `PROJECT_BINARY_DIR` (构建目录)。
        *   **示例**: `project(MyAwesomeApp LANGUAGES CXX)`

    3.  **`add_executable(TargetName source1 [source2 ...])`**:
        *   **作用**: 定义一个可执行文件目标。
        *   **参数**:
            *   `TargetName`: 你想要的可执行文件名 (不含扩展名)。
            *   `source1`, `source2`: 用于编译该目标的源文件列表。
        *   **示例**: `add_executable(my_app main.cpp utils.cpp)`

    4.  **`message([MODE] "message to display" ...)`**:
        *   **作用**: 在 CMake 配置阶段打印消息，用于调试或显示信息。
        *   **常用 MODE**: `STATUS` (普通信息), `WARNING` (警告), `FATAL_ERROR` (错误并终止)。
        *   **示例**: `message(STATUS "Configuring the project...")`

    5.  **`set(VARIABLE value ...)`**:
        *   **作用**: 设置或修改一个 CMake 变量的值。
        *   **示例**:
            *   `set(MY_SOURCES main.cpp utils.cpp)`
            *   `add_executable(my_app ${MY_SOURCES})`
            *   `set(CMAKE_CXX_STANDARD 17)` (设置 C++ 标准)
            *   `set(CMAKE_CXX_STANDARD_REQUIRED True)` (强制使用该标准)

*   **基本构建流程 (命令行)**:
    1.  创建项目目录结构:
        ```
        my_project/
        ├── CMakeLists.txt
        └── main.cpp  # (和其他源文件)
        ```
    2.  编写 `CMakeLists.txt` 和源代码。
    3.  创建构建目录 (推荐在源代码目录之外): `mkdir build && cd build`
    4.  **配置**: `cmake ..` ( `..` 指向上层的 `CMakeLists.txt` 所在目录)
        *   CMake 会检测编译器，并根据 `CMakeLists.txt` 生成本地构建文件 (如 `Makefile`)。
        *   可指定生成器: `cmake -G "Ninja" ..` 或 `cmake -G "Visual Studio 17 2022" ..`
        *   可定义变量: `cmake -DCMAKE_BUILD_TYPE=Release ..` 或 `cmake -DMY_OPTION=ON ..`
    5.  **构建**: `cmake --build .`
        *   这会调用底层的构建工具 (make, ninja, msbuild 等) 来编译和链接。
        *   也可以直接运行: `make` 或 `ninja` (如果在配置时指定了对应生成器)。
    6.  **运行**: `./my_app` (Linux/macOS) 或 `.\Debug\my_app.exe` (Windows/VS 默认)。

## 3. 库的使用与链接 (核心)

*   **目标**: 理解如何创建和使用静态库、动态库，以及如何链接它们。
*   **命令**:

    1.  **`add_library(TargetName [STATIC | SHARED | MODULE] source1 [source2 ...])`**:
        *   **作用**: 定义一个库目标。
        *   **类型**:
            *   `STATIC`: 静态库 (`.a`, `.lib`)。
            *   `SHARED`: 动态库/共享库 (`.so`, `.dll`, `.dylib`)。
            *   `MODULE`: 特殊的动态库，不会被链接，通常用于运行时加载 (如插件)。
        *   **示例**: `add_library(my_utils STATIC utils.cpp helpers.cpp)`

    2.  **`target_link_libraries(TargetName [PRIVATE | PUBLIC | INTERFACE] lib1 [lib2 ...])`**:
        *   **作用**: 将一个或多个库链接到目标 (可执行文件或其他库)。
        *   **参数**:
            *   `TargetName`: 需要链接库的目标 (如 `my_app`)。
            *   `lib1`, `lib2`: 要链接的库名 (必须是 CMake 已知的 Target 名称，如 `my_utils`) 或库文件路径。
        *   **关键字 (重要)**: 控制依赖传递
            *   `PRIVATE`: 链接的库仅 `TargetName` 内部使用。依赖不传递。
            *   `PUBLIC`: 链接的库 `TargetName` 内部使用，并且 **传递** 给链接到 `TargetName` 的其他目标。(既是实现细节也是接口)
            *   `INTERFACE`: 链接的库 `TargetName` 内部 **不** 使用，但 **传递** 给链接到 `TargetName` 的其他目标。(纯接口)
        *   **示例**: `target_link_libraries(my_app PRIVATE my_utils)`

    3.  **`target_include_directories(TargetName [PRIVATE | PUBLIC | INTERFACE] dir1 [dir2 ...])`**:
        *   **作用**: 为目标指定头文件搜索路径。
        *   **参数**:
            *   `TargetName`: 需要包含目录的目标。
            *   `dir1`, `dir2`: 头文件目录路径。可以使用变量如 `${PROJECT_SOURCE_DIR}/include`。
        *   **关键字**: `PRIVATE`, `PUBLIC`, `INTERFACE` 的含义与 `target_link_libraries` 类似，控制包含目录的传递性。
        *   **示例**: `target_include_directories(my_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)` (假设 `my_utils` 的头文件在 `include` 子目录，并希望链接它的目标也能找到这些头文件)

*   **最佳实践**: 优先使用 `target_*` 系列命令，它们提供了更细粒度的控制，是现代 CMake 的推荐做法。避免使用旧的全局命令如 `include_directories()` 和 `link_directories()`。

## 4. 子目录与项目结构

*   **目标**: 管理包含多个子模块或子库的复杂项目。
*   **命令**:

    1.  **`add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])`**:
        *   **作用**: 将子目录添加到构建中。CMake 会进入 `source_dir` 并执行其下的 `CMakeLists.txt`。
        *   **参数**:
            *   `source_dir`: 包含 `CMakeLists.txt` 的子目录路径。
            *   `binary_dir`: (可选) 指定子目录构建文件的输出位置 (相对于当前构建目录)。
            *   `EXCLUDE_FROM_ALL`: (可选) 默认情况下不构建此子目录中的目标 (除非手动指定或被其他目标依赖)。
        *   **示例**: `add_subdirectory(src/my_library)`

*   **典型结构**:
    ```
    project_root/
    ├── CMakeLists.txt        # 顶层 CMakeLists
    ├── src/
    │   ├── CMakeLists.txt    # src 子目录的 CMakeLists
    │   ├── main.cpp
    │   └── app_utils.cpp
    ├── lib/
    │   ├── CMakeLists.txt    # lib 子目录的 CMakeLists
    │   ├── my_library.cpp
    │   └── include/
    │       └── my_library.h
    └── build/                # 构建目录 (通常不加入版本控制)
    ```

## 5. 查找和使用第三方库

*   **目标**: 集成项目外部的库 (如 Boost, OpenSSL, Qt 等)。
*   **命令**:

    1.  **`find_package(<PackageName> [version] [REQUIRED] [[COMPONENTS] [components...]] ...)`**:
        *   **作用**: 查找并加载外部库的配置。CMake 会查找 `Find<PackageName>.cmake` (Module 模式) 或 `<PackageName>Config.cmake` / `<package_name>-config.cmake` (Config 模式) 文件。
        *   **参数**:
            *   `<PackageName>`: 要查找的包名 (大小写敏感，取决于包本身)。
            *   `[version]`: (可选) 需要的最低版本。
            *   `[REQUIRED]`: (可选) 如果找不到包，CMake 会报错并停止。
            *   `[COMPONENTS]`: (可选) 指定需要包的特定组件。
        *   **效果**: 如果成功找到，会设置 `<PackageName>_FOUND` 变量为 TRUE，并定义其他变量，如 `<PackageName>_INCLUDE_DIRS` (头文件路径) 和 `<PackageName>_LIBRARIES` (需要链接的库)。
        *   **示例**:
            ```cmake
            find_package(Boost 1.67 REQUIRED COMPONENTSfilesystem system)
            if(Boost_FOUND)
                message(STATUS "Found Boost: ${Boost_VERSION_STRING}")
                target_include_directories(my_app PRIVATE ${Boost_INCLUDE_DIRS})
                target_link_libraries(my_app PRIVATE ${Boost_LIBRARIES})
            endif()

            find_package(OpenSSL REQUIRED)
            target_link_libraries(my_app PRIVATE OpenSSL::SSL OpenSSL::Crypto) # 现代用法 (如果包提供)
            ```

## 6. 选项、安装与测试

*   **目标**: 增加构建的可配置性，定义安装规则，并集成测试。
*   **命令**:

    1.  **`option(variable "description" [initial value])`**:
        *   **作用**: 定义一个用户可在 CMake 配置时修改的布尔选项 (ON/OFF)。
        *   **示例**: `option(BUILD_TESTS "Build the project tests" ON)` (默认开启测试构建)
        *   **使用**:
            ```cmake
            if(BUILD_TESTS)
                enable_testing()
                add_subdirectory(tests)
            endif()
            ```
        *   **配置时修改**: `cmake .. -DBUILD_TESTS=OFF`

    2.  **`install(...)`**:
        *   **作用**: 定义项目文件在安装时的规则。
        *   **常见用法**:
            *   `install(TARGETS my_app my_utils DESTINATION bin)`: 安装可执行文件和库到安装目录下的 `bin`。
            *   `install(FILES readme.md config.ini DESTINATION etc)`: 安装指定文件到 `etc`。
            *   `install(DIRECTORY include/ DESTINATION include)`: 安装整个 `include` 目录的内容到 `include`。
        *   **安装路径**: `DESTINATION` 是相对于 `CMAKE_INSTALL_PREFIX` 的路径。此变量可以在配置时用 `-DCMAKE_INSTALL_PREFIX=/path/to/install` 指定。
        *   **执行安装**: `cmake --install .` (在构建目录下执行)。

    3.  **`enable_testing()`**:
        *   **作用**: 在当前目录及子目录启用 CTest 测试。

    4.  **`add_test(NAME <test_name> COMMAND <executable> [args...])`**:
        *   **作用**: 添加一个测试用例。
        *   **参数**:
            *   `NAME <test_name>`: 测试的唯一名称。
            *   `COMMAND <executable>`: 要运行的测试程序 (通常是项目构建出的可执行文件)。
            *   `[args...]`: (可选) 传递给测试程序的命令行参数。
        *   **示例**: `add_test(NAME MathTest COMMAND test_math --basic)`
        *   **运行测试**: `ctest` (在构建目录下执行)。

## 7. 进阶主题 (后续探索)

*   **Generator Expressions (生成器表达式)**: 在生成构建系统时才求值的表达式，用于更灵活地处理配置相关的设置 (例如 `$<CONFIG:Debug>`, `$<TARGET_FILE:mytarget>`)。
*   **CPack**: 用于创建二进制和源码安装包 (DEB, RPM, ZIP, NSIS installer 等)。
*   **Custom Commands and Targets (`add_custom_command`, `add_custom_target`)**: 在构建过程中执行自定义脚本或命令 (如代码生成)。
*   **Toolchain Files**: 用于交叉编译或指定特定的编译器、链接器和工具。
*   **FetchContent**: 在配置时从外部获取依赖项 (如 Git 仓库)。
*   **CMake Presets**: `CMakePresets.json` 文件，用于标准化配置和构建选项，方便共享和 CI 集成。

## 8. 学习资源

*   **CMake 官方文档**: [https://cmake.org/documentation/](https://cmake.org/documentation/) (最权威，必备)
*   **CMake 官方教程**: [https://cmake.org/cmake/help/latest/guide/tutorial/index.html](https://cmake.org/cmake/help/latest/guide/tutorial/index.html) (动手入门好材料)
*   **Mastering CMake (书籍)**: 经典教材，注意版本更新。
*   **Effective Modern CMake (在线文章/Gist)**: [https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1](https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1) (现代 CMake 最佳实践总结)
*   **More Modern CMake (文章系列)**: [https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/](https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/)

---

**学习建议**:

1.  **动手实践**: 边学边写，从简单的 Hello World 开始，逐步添加库、子目录和测试。
2.  **理解概念**: 掌握 Target、变量、属性 (Properties) 和依赖传递 (`PUBLIC`/`PRIVATE`/`INTERFACE`) 是关键。
3.  **查阅文档**: 养成查阅 CMake 官方文档的习惯，特别是命令的详细参数和行为。
4.  **拥抱现代 CMake**: 尽量使用 `target_*` 命令，它们提供了更好的封装性和可维护性。
5.  **看优秀项目**: 参考 Github 上优秀的开源 C++ 项目是如何组织 `CMakeLists.txt` 的。
