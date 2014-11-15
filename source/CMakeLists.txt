cmake_minimum_required(VERSION 2.8.4)

project(singularity.json)

include_directories(../include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES
    json.cpp
    json_data.cpp
    json_lexer.cpp
    json_builder.cpp
)

add_library(singularity.json STATIC ${SOURCE_FILES})
