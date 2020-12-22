cmake_minimum_required(VERSION 3.2)

project(A2.2)

set(CMAKE_CXX_STANDARD "14")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp payload.cpp test.cpp trackmymoves.cpp)
add_executable(a2.2 ${SOURCE_FILES})