cmake_minimum_required(VERSION 2.8.4)

project(json)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES example.cpp)

add_subdirectory(source)
add_executable(json ${SOURCE_FILES})
add_dependencies(json so.json)
target_link_libraries(json so.json)
