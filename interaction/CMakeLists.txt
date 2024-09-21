
cmake_minimum_required (VERSION 3.21)
project (os_cw_ntrctn)

add_library (
    os_cw_ntrctn
    src/interaction.cpp)


target_include_directories (
    os_cw_ntrctn
    PUBLIC
    ./include)

target_link_libraries (
    os_cw_ntrctn
    PUBLIC
    os_cw_nnr_rchtctr)

target_link_libraries (
    os_cw_ntrctn
    PUBLIC
    os_cw_lggr_sngltn)

target_link_libraries (
    os_cw_ntrctn
    PUBLIC
    os_cw_ipc)

#set (CMAKE_CXX_FLAGS "-lstdc++fs -std=c++17")

set_target_properties (
    os_cw_ntrctn PROPERTIES
    LANGUAGES CXX
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION 1.0
    DESCRIPTION "inner architecture library")