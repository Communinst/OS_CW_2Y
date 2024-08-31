cmake_minimum_required(VERSION 3.21)
project(os_cw_rlvnt_tp)


add_library(
    os_cw_rlvnt_tp
    src/user.cpp)

target_include_directories(
    os_cw_rlvnt_tp
    PUBLIC
    ./include)

target_link_libraries(
    os_cw_rlvnt_tp
    PUBLIC
    os_cw_flwght_sngltn)

set_target_properties(
    os_cw_rlvnt_tp PROPERTIES
    LANGUAGES CXX
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION 1.0
    DESCRIPTION "relevant type unitr library")

