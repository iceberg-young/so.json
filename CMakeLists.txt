cmake_minimum_required(VERSION 2.8.4)

project(json)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES example.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(source)
add_dependencies(${PROJECT_NAME} so.json)
target_link_libraries(${PROJECT_NAME} so.json)

include(Dependencies.cmake)
