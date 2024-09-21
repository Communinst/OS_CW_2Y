cmake_minimum_required(VERSION 3.21)
project(os_cw_lggr_sngltn)

add_library (
        os_cw_lggr_sngltn
        src/singleton.cpp)

target_include_directories (
        os_cw_lggr_sngltn
        PUBLIC
        ./include)

target_link_libraries (
    os_cw_lggr_sngltn
    PUBLIC
    os_cw_lggr_lggr)

target_link_libraries (
    os_cw_lggr_sngltn
    PUBLIC
    os_cw_lggr_srvr_lggr)

set_target_properties(
        os_cw_lggr_sngltn PROPERTIES
        LANGUAGES CXX
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        VERSION 1.0
        DESCRIPTION "logger interface library")