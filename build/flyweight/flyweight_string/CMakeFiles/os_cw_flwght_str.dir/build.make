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
include flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/compiler_depend.make

# Include the progress variables for this target.
include flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/progress.make

# Include the compile flags for this target's objects.
include flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/flags.make

flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/src/flyweight_string.cpp.obj: flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/flags.make
flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/src/flyweight_string.cpp.obj: flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/includes_CXX.rsp
flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/src/flyweight_string.cpp.obj: C:/Users/Asus/Desktop/Coding/CPP/CourseWorkOpS/flyweight/flyweight_string/src/flyweight_string.cpp
flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/src/flyweight_string.cpp.obj: flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/src/flyweight_string.cpp.obj"
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\flyweight\flyweight_string && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/src/flyweight_string.cpp.obj -MF CMakeFiles\os_cw_flwght_str.dir\src\flyweight_string.cpp.obj.d -o CMakeFiles\os_cw_flwght_str.dir\src\flyweight_string.cpp.obj -c C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\flyweight\flyweight_string\src\flyweight_string.cpp

flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/src/flyweight_string.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/os_cw_flwght_str.dir/src/flyweight_string.cpp.i"
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\flyweight\flyweight_string && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\flyweight\flyweight_string\src\flyweight_string.cpp > CMakeFiles\os_cw_flwght_str.dir\src\flyweight_string.cpp.i

flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/src/flyweight_string.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/os_cw_flwght_str.dir/src/flyweight_string.cpp.s"
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\flyweight\flyweight_string && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\flyweight\flyweight_string\src\flyweight_string.cpp -o CMakeFiles\os_cw_flwght_str.dir\src\flyweight_string.cpp.s

# Object files for target os_cw_flwght_str
os_cw_flwght_str_OBJECTS = \
"CMakeFiles/os_cw_flwght_str.dir/src/flyweight_string.cpp.obj"

# External object files for target os_cw_flwght_str
os_cw_flwght_str_EXTERNAL_OBJECTS =

flyweight/flyweight_string/libos_cw_flwght_str.a: flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/src/flyweight_string.cpp.obj
flyweight/flyweight_string/libos_cw_flwght_str.a: flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/build.make
flyweight/flyweight_string/libos_cw_flwght_str.a: flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libos_cw_flwght_str.a"
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\flyweight\flyweight_string && $(CMAKE_COMMAND) -P CMakeFiles\os_cw_flwght_str.dir\cmake_clean_target.cmake
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\flyweight\flyweight_string && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\os_cw_flwght_str.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/build: flyweight/flyweight_string/libos_cw_flwght_str.a
.PHONY : flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/build

flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/clean:
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\flyweight\flyweight_string && $(CMAKE_COMMAND) -P CMakeFiles\os_cw_flwght_str.dir\cmake_clean.cmake
.PHONY : flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/clean

flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\flyweight\flyweight_string C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\flyweight\flyweight_string C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\flyweight\flyweight_string\CMakeFiles\os_cw_flwght_str.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : flyweight/flyweight_string/CMakeFiles/os_cw_flwght_str.dir/depend

