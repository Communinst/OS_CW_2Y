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
CMAKE_SOURCE_DIR = X:\Coding\CPP\mp_os

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = X:\Coding\CPP\mp_os\build

# Include any dependencies generated for this target.
include arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/compiler_depend.make

# Include the progress variables for this target.
include arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/progress.make

# Include the compile flags for this target's objects.
include arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/flags.make

arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/src/fraction.cpp.obj: arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/flags.make
arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/src/fraction.cpp.obj: arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/includes_CXX.rsp
arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/src/fraction.cpp.obj: X:/Coding/CPP/mp_os/arithmetic/fraction/src/fraction.cpp
arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/src/fraction.cpp.obj: arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=X:\Coding\CPP\mp_os\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/src/fraction.cpp.obj"
	cd /d X:\Coding\CPP\mp_os\build\arithmetic\fraction && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/src/fraction.cpp.obj -MF CMakeFiles\mp_os_arthmtc_frctn.dir\src\fraction.cpp.obj.d -o CMakeFiles\mp_os_arthmtc_frctn.dir\src\fraction.cpp.obj -c X:\Coding\CPP\mp_os\arithmetic\fraction\src\fraction.cpp

arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/src/fraction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mp_os_arthmtc_frctn.dir/src/fraction.cpp.i"
	cd /d X:\Coding\CPP\mp_os\build\arithmetic\fraction && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E X:\Coding\CPP\mp_os\arithmetic\fraction\src\fraction.cpp > CMakeFiles\mp_os_arthmtc_frctn.dir\src\fraction.cpp.i

arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/src/fraction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mp_os_arthmtc_frctn.dir/src/fraction.cpp.s"
	cd /d X:\Coding\CPP\mp_os\build\arithmetic\fraction && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S X:\Coding\CPP\mp_os\arithmetic\fraction\src\fraction.cpp -o CMakeFiles\mp_os_arthmtc_frctn.dir\src\fraction.cpp.s

# Object files for target mp_os_arthmtc_frctn
mp_os_arthmtc_frctn_OBJECTS = \
"CMakeFiles/mp_os_arthmtc_frctn.dir/src/fraction.cpp.obj"

# External object files for target mp_os_arthmtc_frctn
mp_os_arthmtc_frctn_EXTERNAL_OBJECTS =

arithmetic/fraction/libmp_os_arthmtc_frctn.a: arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/src/fraction.cpp.obj
arithmetic/fraction/libmp_os_arthmtc_frctn.a: arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/build.make
arithmetic/fraction/libmp_os_arthmtc_frctn.a: arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=X:\Coding\CPP\mp_os\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmp_os_arthmtc_frctn.a"
	cd /d X:\Coding\CPP\mp_os\build\arithmetic\fraction && $(CMAKE_COMMAND) -P CMakeFiles\mp_os_arthmtc_frctn.dir\cmake_clean_target.cmake
	cd /d X:\Coding\CPP\mp_os\build\arithmetic\fraction && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mp_os_arthmtc_frctn.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/build: arithmetic/fraction/libmp_os_arthmtc_frctn.a
.PHONY : arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/build

arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/clean:
	cd /d X:\Coding\CPP\mp_os\build\arithmetic\fraction && $(CMAKE_COMMAND) -P CMakeFiles\mp_os_arthmtc_frctn.dir\cmake_clean.cmake
.PHONY : arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/clean

arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" X:\Coding\CPP\mp_os X:\Coding\CPP\mp_os\arithmetic\fraction X:\Coding\CPP\mp_os\build X:\Coding\CPP\mp_os\build\arithmetic\fraction X:\Coding\CPP\mp_os\build\arithmetic\fraction\CMakeFiles\mp_os_arthmtc_frctn.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : arithmetic/fraction/CMakeFiles/mp_os_arthmtc_frctn.dir/depend

