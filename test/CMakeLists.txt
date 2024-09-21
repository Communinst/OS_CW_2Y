cmake_minimum_required(VERSION 3.21)
project(os_cw_test)


add_executable (
    os_cw_test
    mrn.cpp)
 
target_link_libraries (
    os_cw_test
    PUBLIC
    os_cw_ntrctn)

set_target_properties (
    os_cw_test PROPERTIES
    LANGUAGES CXX
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION 1.0
    DESCRIPTION "Just test")