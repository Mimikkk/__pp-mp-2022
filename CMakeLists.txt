cmake_minimum_required(VERSION 3.22)
project(pp-2022 CXX)

set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})

file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.hpp ${SRC_DIR}/*.cpp)

find_package(OpenMP REQUIRED)
add_executable(solver src/main.cpp ${SOURCES})
target_link_libraries(solver PRIVATE OpenMP::OpenMP_CXX)
