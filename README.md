# C_types: C 语言高级数据结构库

C_types 是一个为 C 语言提供的高级数据结构集合。它巧妙地利用 GCC/Clang 扩展（`typeof` 和语句表达式）来提供类型安全的宏接口，使得调用代码更简洁、更安全。

**注意：** 本库依赖 GNU 扩展，因此仅适用于 **GCC** 和 **Clang** 编译器，无法在 MSVC (Visual Studio) 上编译。

## 功能特性

本项目提供了以下数据结构：

* **List (动态数组):** (来自 `list.h`)
    * `list` 结构体
    * 类型安全的宏：`list_create(type)`, `list_append(l_ptr, value)`, `list_get(type, l_ptr, index)` 等。
* **Stack (栈):** (来自 `container.h`)
    * `stack` 结构体
    * 类型安全的宏：`stack_create(type)`, `stack_push(s_ptr, value)`, `stack_pop(type, s_ptr)`, `stack_top(type, s_ptr)`。
* **Queue (队列):** (来自 `container.h`)
    * `queue` 结构体
    * 类型安全的宏：`queue_create(type, size)`, `queue_push(q_ptr, value)`, `queue_front(type, q_ptr)` 等。
* **String (字符串):** (来自 `str.h`)
    * `string_t` 结构体 (带长度的字符串) 和 `str_view` (字符串视图)。
    * `string(value)` 宏：可将 `char*`, `int`, `double` 等自动转换为一个（内部管理的）`string_t`。
    * **警告：** `string()` 和 `str_static()` 函数使用全局静态池，**非线程安全**。
* **Map (字典):** (来自 `mapping.h`)
    * `map`: (char* -> int) 的映射。
    * `dict`: (char* -> char*) 的映射。
    * **注意：** 当前实现基于线性扫描（O(N) 复杂度），而非哈希表。

## 如何使用 (两种方式)

你可以通过两种方式将此库集成到你的项目中：

---

### 方式一：Header-Only 模式 (推荐用于小型项目)

本库支持作为纯头文件库使用。你不需要编译任何 `.c` 文件或链接任何库。

1.  将本项目的 `include/` 和 `src/` 目录复制到你的项目中。
2.  在你项目的主程序（或某个全局 C 文件）中，**有且仅有一次**，在包含 `c_types.h` 之前定义 `LOAD_C_TYPES_SRC`。

**示例 (`main.c`):**

```c
// 确保在 include 之前定义这个宏
// 这会告诉 c_types.h 把所有 src/*.c 文件也包含进来
#define LOAD_C_TYPES_SRC 

#include "c_types/include/c_types.h"
#include <stdio.h>

int main() {
    // ... 在这里使用 list, map 等 ...
    
    // (确保你的编译器 include 路径包含了 "c_types/include")
    // gcc main.c -I/path/to/c_types/include -o my_app
    return 0;
}
```

-----

### 方式二：使用 CMake 编译和链接 (推荐用于大型项目)

本库提供 `CMakeLists.txt` 文件，可以被编译为一个独立的库（静态或动态），然后被你的主项目链接。


1.  **c\_types 的 CMakeLists.txt** 应使用我们提供的版本（见上文）。
2.  **你的主项目 (your\_project/CMakeLists.txt)** 应该如下所示：

```cmake
cmake_minimum_required(VERSION 3.14)
project(my_app C)

# 1. Use FetchContent module to include c_types
include(FetchContent)

# 2. Declare c_types as a dependency
FetchContent_Declare(
    c_types_deps
    GIT_REPOSITORY  https://github.com/wujunkai2004/C_types.git
    GIT_TAG         main
)

# 3. Download and Compile c_types
FetchContent_MakeAvailable(c_types_deps)

# 4. Now you can link c_types to your executable
target_link_libraries(your_app PRIVATE c_types)
```

3.  **你的 main.c** 现在可以正常包含头文件（不需要 `LOAD_C_TYPES_SRC` 宏）：

<!-- end list -->

```c
#include <c_types.h> // 因为 CMake 自动添加了 include 路径，所以可以直接使用尖括号
#include <stdio.h>

int main() {
    // ... 在这里使用 ...
    return 0;
}
```

## API 使用示例

```c
#include <c_types.h> // 假设已通过 CMake 或 Header-Only 模式正确设置
#include <stdio.h>

void list_example() {
    printf("--- List Example ---\n");
    // 1. 创建一个存储 int 的 list
    list my_list = list_create(int);

    // 2. 添加元素
    list_append(&my_list, 10);
    list_append(&my_list, 20);
    list_append(&my_list, 30);

    // 3. 遍历和获取元素 (使用类型安全的宏)
    for(int i = 0; i < my_list.length; i++) {
        int val = list_get(int, &my_list, i);
        printf("Index %d = %d\n", i, val);
    }
    
    // 4. 释放内存
    list_free(&my_list);
}

void string_example() {
    printf("--- String Example ---\n");
    
    // 使用 string() 宏从不同类型创建 string_t
    string_t s1 = string("Hello World");
    string_t s_int = string(12345);
    string_t s_double = string(3.14159);
    
    printf("String 1: %s (Size: %d)\n", s1.data, s1.size);
    printf("Int-String: %s\n", s_int.data);
    printf("Double-String: %s\n", s_double.data);
    
    // 注意：str_static/string() 创建的字符串由内部静态池管理，不需要手动 free。
    // 警告：此功能非线程安全！
}

void map_example() {
    printf("--- Map (dict) Example ---\n");
    dict my_dict = dict_create();
    
    dict_set(&my_dict, "user", "Alice");
    dict_set(&my_dict, "id", "1001");
    
    // 注意：在 mapping.h 修复 bug 后，这里应该传入 char*
    printf("User is: %s\n", dict_get(&my_dict, "user"));
    printf("ID is: %s\n", dict_get(&my_dict, "id"));
    
    dict_free(&my_dict);
}


int main() {
    list_example();
    string_example();
    map_example();
    return 0;
}
```

```
```