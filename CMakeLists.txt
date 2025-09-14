# c_types/CMakeLists.txt

# 1. Minimum CMake version and project name
cmake_minimum_required(VERSION 3.10)
project(c_types C)

# 2. Find all source files
# Use GLOB to automatically collect all .c files in the src directory
file(GLOB C_TYPES_SOURCES "src/*.c")

# 3. Add library target
# We create it as a library target (default is static library .a)
add_library(c_types ${C_TYPES_SOURCES})

# 4. Export Include directory (key point)
# Set the include folder as PUBLIC.
# This means:
# (A) The c_types target itself will include it during compilation.
# (B) Any external project linking to c_types (such as your linux_work)
#     will automatically get this include path.
target_include_directories(c_types
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 5. Set C standard and extensions
# Since the codebase uses GNU extensions (such as typeof),
# we must ensure C extensions are enabled (or directly specify gnu11 standard)
# Otherwise, if the compiler is in strict standard mode (std=c11), compilation will fail.
set_target_properties(c_types PROPERTIES C_STANDARD 11 C_EXTENSIONS ON)