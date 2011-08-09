cmake_minimum_required(VERSION 2.8)

# project name
project(Box2DSFML)

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")

# define the build type
set(CMAKE_BUILD_TYPE Release)

# add the header path
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/src/box2dsfml DESTINATION ${PROJECT_SOURCE_DIR})

# add the subdirectories
add_subdirectory(src)






