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
CMAKE_COMMAND = C:\CMake\bin\cmake.exe

# The command to remove a file.
RM = C:\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build

# Include any dependencies generated for this target.
include interaction/CMakeFiles/os_cw_ntrctn.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include interaction/CMakeFiles/os_cw_ntrctn.dir/compiler_depend.make

# Include the progress variables for this target.
include interaction/CMakeFiles/os_cw_ntrctn.dir/progress.make

# Include the compile flags for this target's objects.
include interaction/CMakeFiles/os_cw_ntrctn.dir/flags.make

interaction/CMakeFiles/os_cw_ntrctn.dir/src/interaction.cpp.obj: interaction/CMakeFiles/os_cw_ntrctn.dir/flags.make
interaction/CMakeFiles/os_cw_ntrctn.dir/src/interaction.cpp.obj: interaction/CMakeFiles/os_cw_ntrctn.dir/includes_CXX.rsp
interaction/CMakeFiles/os_cw_ntrctn.dir/src/interaction.cpp.obj: C:/Users/Asus/Desktop/Coding/CPP/CourseWorkOpS/interaction/src/interaction.cpp
interaction/CMakeFiles/os_cw_ntrctn.dir/src/interaction.cpp.obj: interaction/CMakeFiles/os_cw_ntrctn.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object interaction/CMakeFiles/os_cw_ntrctn.dir/src/interaction.cpp.obj"
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\interaction && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT interaction/CMakeFiles/os_cw_ntrctn.dir/src/interaction.cpp.obj -MF CMakeFiles\os_cw_ntrctn.dir\src\interaction.cpp.obj.d -o CMakeFiles\os_cw_ntrctn.dir\src\interaction.cpp.obj -c C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\interaction\src\interaction.cpp

interaction/CMakeFiles/os_cw_ntrctn.dir/src/interaction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/os_cw_ntrctn.dir/src/interaction.cpp.i"
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\interaction && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\interaction\src\interaction.cpp > CMakeFiles\os_cw_ntrctn.dir\src\interaction.cpp.i

interaction/CMakeFiles/os_cw_ntrctn.dir/src/interaction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/os_cw_ntrctn.dir/src/interaction.cpp.s"
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\interaction && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\interaction\src\interaction.cpp -o CMakeFiles\os_cw_ntrctn.dir\src\interaction.cpp.s

# Object files for target os_cw_ntrctn
os_cw_ntrctn_OBJECTS = \
"CMakeFiles/os_cw_ntrctn.dir/src/interaction.cpp.obj"

# External object files for target os_cw_ntrctn
os_cw_ntrctn_EXTERNAL_OBJECTS =

interaction/libos_cw_ntrctn.a: interaction/CMakeFiles/os_cw_ntrctn.dir/src/interaction.cpp.obj
interaction/libos_cw_ntrctn.a: interaction/CMakeFiles/os_cw_ntrctn.dir/build.make
interaction/libos_cw_ntrctn.a: interaction/CMakeFiles/os_cw_ntrctn.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libos_cw_ntrctn.a"
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\interaction && $(CMAKE_COMMAND) -P CMakeFiles\os_cw_ntrctn.dir\cmake_clean_target.cmake
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\interaction && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\os_cw_ntrctn.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
interaction/CMakeFiles/os_cw_ntrctn.dir/build: interaction/libos_cw_ntrctn.a
.PHONY : interaction/CMakeFiles/os_cw_ntrctn.dir/build

interaction/CMakeFiles/os_cw_ntrctn.dir/clean:
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\interaction && $(CMAKE_COMMAND) -P CMakeFiles\os_cw_ntrctn.dir\cmake_clean.cmake
.PHONY : interaction/CMakeFiles/os_cw_ntrctn.dir/clean

interaction/CMakeFiles/os_cw_ntrctn.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\interaction C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\interaction C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\interaction\CMakeFiles\os_cw_ntrctn.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : interaction/CMakeFiles/os_cw_ntrctn.dir/depend

