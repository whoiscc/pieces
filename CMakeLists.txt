cmake_minimum_required(VERSION 3.12)

project(Pieces LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

set(CXX_STANDARD 14)

add_subdirectory(Source)
add_subdirectory(Tests)
