cmake_minimum_required(VERSION 3.2)

project(so.json)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SOURCE_FILES
    json.cpp
    json_data.cpp
    json_null.cpp
    json_boolean.cpp
    json_number.cpp
    json_string.cpp
    json_array.cpp
    json_object.cpp
    json_parser.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
include_directories(../include)
include(Dependencies.cmake)
