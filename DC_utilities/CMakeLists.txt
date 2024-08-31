cmake_minimum_required (VERSION 3.21)
project(os_cw_dc_utlts)



add_library (
    os_cw_dc_utlts
    src/dc_utilities.cpp)

target_include_directories (
    os_cw_dc_utlts
    PUBLIC
    ./include)

set_target_properties (
    os_cw_dc_utlts PROPERTIES
    LANGUAGES CXX
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION 1.0
    DESCRIPTION "Basic utilities of DarnCommunist")

