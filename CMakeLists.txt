cmake_minimum_required(VERSION 3.24)

project(memo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-stdlib=libc++)
add_link_options(-stdlib=libc++)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)

# Generate CTestTestfile.cmake in current and sub build folders,
# with it the command `ctest` can work
enable_testing()

add_subdirectory(tests)
