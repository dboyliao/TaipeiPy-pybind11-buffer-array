cmake_minimum_required(VERSION 3.2)
project(python_example)

add_subdirectory(thirdparty/pybind11)

set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB_RECURSE MYLIB_SRC "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.c")
pybind11_add_module(_mylib MODULE ${MYLIB_SRC})
target_include_directories(_mylib PRIVATE include)
set_target_properties(
    _mylib
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/mylib
)