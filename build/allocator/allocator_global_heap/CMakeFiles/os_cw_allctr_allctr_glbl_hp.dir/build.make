# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = X:\CMake\bin\cmake.exe

# The command to remove a file.
RM = X:\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = X:\Coding\CPP\CourseWorkOpS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = X:\Coding\CPP\CourseWorkOpS\build

# Include any dependencies generated for this target.
include allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/compiler_depend.make

# Include the progress variables for this target.
include allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/progress.make

# Include the compile flags for this target's objects.
include allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/flags.make

allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/src/allocator_global_heap.cpp.obj: allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/flags.make
allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/src/allocator_global_heap.cpp.obj: allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/includes_CXX.rsp
allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/src/allocator_global_heap.cpp.obj: X:/Coding/CPP/CourseWorkOpS/allocator/allocator_global_heap/src/allocator_global_heap.cpp
allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/src/allocator_global_heap.cpp.obj: allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=X:\Coding\CPP\CourseWorkOpS\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/src/allocator_global_heap.cpp.obj"
	cd /d X:\Coding\CPP\CourseWorkOpS\build\allocator\allocator_global_heap && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/src/allocator_global_heap.cpp.obj -MF CMakeFiles\os_cw_allctr_allctr_glbl_hp.dir\src\allocator_global_heap.cpp.obj.d -o CMakeFiles\os_cw_allctr_allctr_glbl_hp.dir\src\allocator_global_heap.cpp.obj -c X:\Coding\CPP\CourseWorkOpS\allocator\allocator_global_heap\src\allocator_global_heap.cpp

allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/src/allocator_global_heap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/src/allocator_global_heap.cpp.i"
	cd /d X:\Coding\CPP\CourseWorkOpS\build\allocator\allocator_global_heap && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E X:\Coding\CPP\CourseWorkOpS\allocator\allocator_global_heap\src\allocator_global_heap.cpp > CMakeFiles\os_cw_allctr_allctr_glbl_hp.dir\src\allocator_global_heap.cpp.i

allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/src/allocator_global_heap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/src/allocator_global_heap.cpp.s"
	cd /d X:\Coding\CPP\CourseWorkOpS\build\allocator\allocator_global_heap && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S X:\Coding\CPP\CourseWorkOpS\allocator\allocator_global_heap\src\allocator_global_heap.cpp -o CMakeFiles\os_cw_allctr_allctr_glbl_hp.dir\src\allocator_global_heap.cpp.s

# Object files for target os_cw_allctr_allctr_glbl_hp
os_cw_allctr_allctr_glbl_hp_OBJECTS = \
"CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/src/allocator_global_heap.cpp.obj"

# External object files for target os_cw_allctr_allctr_glbl_hp
os_cw_allctr_allctr_glbl_hp_EXTERNAL_OBJECTS =

allocator/allocator_global_heap/libos_cw_allctr_allctr_glbl_hp.a: allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/src/allocator_global_heap.cpp.obj
allocator/allocator_global_heap/libos_cw_allctr_allctr_glbl_hp.a: allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/build.make
allocator/allocator_global_heap/libos_cw_allctr_allctr_glbl_hp.a: allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=X:\Coding\CPP\CourseWorkOpS\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libos_cw_allctr_allctr_glbl_hp.a"
	cd /d X:\Coding\CPP\CourseWorkOpS\build\allocator\allocator_global_heap && $(CMAKE_COMMAND) -P CMakeFiles\os_cw_allctr_allctr_glbl_hp.dir\cmake_clean_target.cmake
	cd /d X:\Coding\CPP\CourseWorkOpS\build\allocator\allocator_global_heap && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\os_cw_allctr_allctr_glbl_hp.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/build: allocator/allocator_global_heap/libos_cw_allctr_allctr_glbl_hp.a
.PHONY : allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/build

allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/clean:
	cd /d X:\Coding\CPP\CourseWorkOpS\build\allocator\allocator_global_heap && $(CMAKE_COMMAND) -P CMakeFiles\os_cw_allctr_allctr_glbl_hp.dir\cmake_clean.cmake
.PHONY : allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/clean

allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" X:\Coding\CPP\CourseWorkOpS X:\Coding\CPP\CourseWorkOpS\allocator\allocator_global_heap X:\Coding\CPP\CourseWorkOpS\build X:\Coding\CPP\CourseWorkOpS\build\allocator\allocator_global_heap X:\Coding\CPP\CourseWorkOpS\build\allocator\allocator_global_heap\CMakeFiles\os_cw_allctr_allctr_glbl_hp.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : allocator/allocator_global_heap/CMakeFiles/os_cw_allctr_allctr_glbl_hp.dir/depend

