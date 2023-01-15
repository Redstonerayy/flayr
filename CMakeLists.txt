CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

set(CMAKE_CXX_FLAGS "-Wall -std=c++20 -O2")

project(flayr)

# build libary
FILE(GLOB_RECURSE LIB_FILES src/flayr/*.cpp)
add_library(flayr ${LIB_FILES})
target_include_directories(flayr PRIVATE
    src
)

# build project
FILE(GLOB_RECURSE TARGET_FILES src/target/*.cpp)
add_executable(target ${TARGET_FILES})
target_include_directories(target PRIVATE
    src
)

target_link_libraries(target flayr)
