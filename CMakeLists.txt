cmake_minimum_required(VERSION 3.21)
project(os_cw)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory (allocator)
add_subdirectory (IPC)
add_subdirectory (associative_container)
add_subdirectory (common)
add_subdirectory (inner_architecture)
add_subdirectory (command)
add_subdirectory (COR)
add_subdirectory (logger)
add_subdirectory (flyweight)
add_subdirectory (relevant_type)


add_subdirectory (interaction)
 
 
add_subdirectory (test)
 
add_subdirectory (DC_utilities)