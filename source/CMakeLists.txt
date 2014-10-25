cmake_minimum_required(VERSION 2.8.4)
project(singularity.json)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fvisibility=hidden -fvisibility-inlines-hidden")
set(SOURCE_FILES
    json.cpp
    json_data.cpp
    json_undefined.cpp
    json_null.cpp
    json_boolean.cpp
    json_decimal.cpp
    json_integer.cpp
    json_string.cpp
    json_array.cpp
    json_object.cpp
)

include_directories(../include)

add_library(singularity.json STATIC ${SOURCE_FILES})
