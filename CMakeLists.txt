cmake_minimum_required(VERSION 3.0)

project(sphCPP)

set(CMAKE_BUILD_TYPE Debug)

include_directories(${PROJECT_SOURCE_DIR}/include)
message(STATUS "${PROJECT_SOURCE_DIR}")
find_package(PythonLibs 3)

add_subdirectory(sph)
