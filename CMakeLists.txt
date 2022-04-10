cmake_minimum_required(VERSION 3.22)
project(pp_2022)

set(CMAKE_CXX_STANDARD 23)

# Source directories and files
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

# Executable output directory
set(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})

file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.hpp ${SRC_DIR}/*.cpp)

find_package(OpenMP REQUIRED)
add_executable(solver src/main.cpp ${SOURCES})
target_link_libraries(solver PRIVATE OpenMP::OpenMP_CXX)
