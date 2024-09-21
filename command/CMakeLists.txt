
cmake_minimum_required (VERSION 3.21)
project (os_cw_cmmd_pttrn)

add_library(
    os_cw_cmmd_pttrn
    src/command.cpp)

target_include_directories (
    os_cw_cmmd_pttrn
    PUBLIC
    ./include)

target_link_libraries (
    os_cw_cmmd_pttrn
    PUBLIC
    os_cw_nnr_rchtctr)


#set (CMAKE_CXX_FLAGS "-lstdc++fs -std=c++17")

set_target_properties (
    os_cw_cmmd_pttrn PROPERTIES
    LANGUAGES CXX
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION 1.0
    DESCRIPTION "inner architecture library")