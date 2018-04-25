project(MyHello CXX)
cmake_minimum_required(VERSION 2.8)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE TOOLS_SOURCES "*.cpp")
file(GLOB_RECURSE TOOLS_HEADERS "*.h")

set (TOOLS_INCLUDE_DIRS "")
foreach (_headerFile ${TOOLS_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND TOOLS_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES TOOLS_INCLUDE_DIRS)

add_library(tools ${TOOLS_SOURCES})
target_include_directories(tools PRIVATE ${TOOLS_INCLUDE_DIRS})