cmake_minimum_required(VERSION 3.21)
project(os_cw_flwght_str)

add_subdirectory(singleton)

add_library(
    os_cw_flwght_str
    src/flyweight_string.cpp)

target_include_directories(
    os_cw_flwght_str
    PUBLIC
    ./include)

set_target_properties(
    os_cw_flwght_str PROPERTIES
    LANGUAGES CXX
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION 1.0
    DESCRIPTION "flyweight string unit library")