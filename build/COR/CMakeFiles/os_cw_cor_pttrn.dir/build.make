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
include COR/CMakeFiles/os_cw_cor_pttrn.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include COR/CMakeFiles/os_cw_cor_pttrn.dir/compiler_depend.make

# Include the progress variables for this target.
include COR/CMakeFiles/os_cw_cor_pttrn.dir/progress.make

# Include the compile flags for this target's objects.
include COR/CMakeFiles/os_cw_cor_pttrn.dir/flags.make

COR/CMakeFiles/os_cw_cor_pttrn.dir/src/handlers.cpp.obj: COR/CMakeFiles/os_cw_cor_pttrn.dir/flags.make
COR/CMakeFiles/os_cw_cor_pttrn.dir/src/handlers.cpp.obj: COR/CMakeFiles/os_cw_cor_pttrn.dir/includes_CXX.rsp
COR/CMakeFiles/os_cw_cor_pttrn.dir/src/handlers.cpp.obj: X:/Coding/CPP/CourseWorkOpS/COR/src/handlers.cpp
COR/CMakeFiles/os_cw_cor_pttrn.dir/src/handlers.cpp.obj: COR/CMakeFiles/os_cw_cor_pttrn.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=X:\Coding\CPP\CourseWorkOpS\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object COR/CMakeFiles/os_cw_cor_pttrn.dir/src/handlers.cpp.obj"
	cd /d X:\Coding\CPP\CourseWorkOpS\build\COR && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT COR/CMakeFiles/os_cw_cor_pttrn.dir/src/handlers.cpp.obj -MF CMakeFiles\os_cw_cor_pttrn.dir\src\handlers.cpp.obj.d -o CMakeFiles\os_cw_cor_pttrn.dir\src\handlers.cpp.obj -c X:\Coding\CPP\CourseWorkOpS\COR\src\handlers.cpp

COR/CMakeFiles/os_cw_cor_pttrn.dir/src/handlers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/os_cw_cor_pttrn.dir/src/handlers.cpp.i"
	cd /d X:\Coding\CPP\CourseWorkOpS\build\COR && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E X:\Coding\CPP\CourseWorkOpS\COR\src\handlers.cpp > CMakeFiles\os_cw_cor_pttrn.dir\src\handlers.cpp.i

COR/CMakeFiles/os_cw_cor_pttrn.dir/src/handlers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/os_cw_cor_pttrn.dir/src/handlers.cpp.s"
	cd /d X:\Coding\CPP\CourseWorkOpS\build\COR && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S X:\Coding\CPP\CourseWorkOpS\COR\src\handlers.cpp -o CMakeFiles\os_cw_cor_pttrn.dir\src\handlers.cpp.s

# Object files for target os_cw_cor_pttrn
os_cw_cor_pttrn_OBJECTS = \
"CMakeFiles/os_cw_cor_pttrn.dir/src/handlers.cpp.obj"

# External object files for target os_cw_cor_pttrn
os_cw_cor_pttrn_EXTERNAL_OBJECTS =

COR/libos_cw_cor_pttrn.a: COR/CMakeFiles/os_cw_cor_pttrn.dir/src/handlers.cpp.obj
COR/libos_cw_cor_pttrn.a: COR/CMakeFiles/os_cw_cor_pttrn.dir/build.make
COR/libos_cw_cor_pttrn.a: COR/CMakeFiles/os_cw_cor_pttrn.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=X:\Coding\CPP\CourseWorkOpS\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libos_cw_cor_pttrn.a"
	cd /d X:\Coding\CPP\CourseWorkOpS\build\COR && $(CMAKE_COMMAND) -P CMakeFiles\os_cw_cor_pttrn.dir\cmake_clean_target.cmake
	cd /d X:\Coding\CPP\CourseWorkOpS\build\COR && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\os_cw_cor_pttrn.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
COR/CMakeFiles/os_cw_cor_pttrn.dir/build: COR/libos_cw_cor_pttrn.a
.PHONY : COR/CMakeFiles/os_cw_cor_pttrn.dir/build

COR/CMakeFiles/os_cw_cor_pttrn.dir/clean:
	cd /d X:\Coding\CPP\CourseWorkOpS\build\COR && $(CMAKE_COMMAND) -P CMakeFiles\os_cw_cor_pttrn.dir\cmake_clean.cmake
.PHONY : COR/CMakeFiles/os_cw_cor_pttrn.dir/clean

COR/CMakeFiles/os_cw_cor_pttrn.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" X:\Coding\CPP\CourseWorkOpS X:\Coding\CPP\CourseWorkOpS\COR X:\Coding\CPP\CourseWorkOpS\build X:\Coding\CPP\CourseWorkOpS\build\COR X:\Coding\CPP\CourseWorkOpS\build\COR\CMakeFiles\os_cw_cor_pttrn.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : COR/CMakeFiles/os_cw_cor_pttrn.dir/depend

