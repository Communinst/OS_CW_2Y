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
include test/CMakeFiles/os_cw_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/os_cw_test.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/os_cw_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/os_cw_test.dir/flags.make

test/CMakeFiles/os_cw_test.dir/mrn.cpp.obj: test/CMakeFiles/os_cw_test.dir/flags.make
test/CMakeFiles/os_cw_test.dir/mrn.cpp.obj: test/CMakeFiles/os_cw_test.dir/includes_CXX.rsp
test/CMakeFiles/os_cw_test.dir/mrn.cpp.obj: C:/Users/Asus/Desktop/Coding/CPP/CourseWorkOpS/test/mrn.cpp
test/CMakeFiles/os_cw_test.dir/mrn.cpp.obj: test/CMakeFiles/os_cw_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/os_cw_test.dir/mrn.cpp.obj"
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\test && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/os_cw_test.dir/mrn.cpp.obj -MF CMakeFiles\os_cw_test.dir\mrn.cpp.obj.d -o CMakeFiles\os_cw_test.dir\mrn.cpp.obj -c C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\test\mrn.cpp

test/CMakeFiles/os_cw_test.dir/mrn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/os_cw_test.dir/mrn.cpp.i"
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\test && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\test\mrn.cpp > CMakeFiles\os_cw_test.dir\mrn.cpp.i

test/CMakeFiles/os_cw_test.dir/mrn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/os_cw_test.dir/mrn.cpp.s"
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\test && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\test\mrn.cpp -o CMakeFiles\os_cw_test.dir\mrn.cpp.s

# Object files for target os_cw_test
os_cw_test_OBJECTS = \
"CMakeFiles/os_cw_test.dir/mrn.cpp.obj"

# External object files for target os_cw_test
os_cw_test_EXTERNAL_OBJECTS =

test/os_cw_test.exe: test/CMakeFiles/os_cw_test.dir/mrn.cpp.obj
test/os_cw_test.exe: test/CMakeFiles/os_cw_test.dir/build.make
test/os_cw_test.exe: interaction/libos_cw_ntrctn.a
test/os_cw_test.exe: inner_architecture/libos_cw_nnr_rchtctr.a
test/os_cw_test.exe: COR/libos_cw_cor_pttrn.a
test/os_cw_test.exe: command/libos_cw_cmmd_pttrn.a
test/os_cw_test.exe: inner_architecture/libos_cw_nnr_rchtctr.a
test/os_cw_test.exe: COR/libos_cw_cor_pttrn.a
test/os_cw_test.exe: command/libos_cw_cmmd_pttrn.a
test/os_cw_test.exe: relevant_type/libos_cw_rlvnt_tp.a
test/os_cw_test.exe: associative_container/search_tree/indexing_tree/b_tree/libos_cw_assctv_cntnr_srch_tr_indxng_tr_b_tr.a
test/os_cw_test.exe: logger/client_logger/libos_cw_lggr_clnt_lggr.a
test/os_cw_test.exe: associative_container/search_tree/libos_cw_assctv_cntnr_srch_tr.a
test/os_cw_test.exe: associative_container/libos_cw_assctv_cntnr.a
test/os_cw_test.exe: DC_utilities/libos_cw_dc_utlts.a
test/os_cw_test.exe: flyweight/flyweight_string/singleton/libos_cw_flwght_sngltn.a
test/os_cw_test.exe: flyweight/flyweight_string/libos_cw_flwght_str.a
test/os_cw_test.exe: allocator/allocator_global_heap/libos_cw_allctr_allctr_glbl_hp.a
test/os_cw_test.exe: allocator/allocator_boundary_tags/libos_cw_allctr_allctr_bndr_tgs.a
test/os_cw_test.exe: logger/logger_singleton/libos_cw_lggr_sngltn.a
test/os_cw_test.exe: logger/server_logger/libos_cw_lggr_srvr_lggr.a
test/os_cw_test.exe: logger/logger/libos_cw_lggr_lggr.a
test/os_cw_test.exe: common/libos_cw_cmmn.a
test/os_cw_test.exe: IPC/libos_cw_ipc.a
test/os_cw_test.exe: allocator/allocator/libos_cw_allctr_allctr.a
test/os_cw_test.exe: test/CMakeFiles/os_cw_test.dir/linkLibs.rsp
test/os_cw_test.exe: test/CMakeFiles/os_cw_test.dir/objects1.rsp
test/os_cw_test.exe: test/CMakeFiles/os_cw_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable os_cw_test.exe"
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\os_cw_test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/os_cw_test.dir/build: test/os_cw_test.exe
.PHONY : test/CMakeFiles/os_cw_test.dir/build

test/CMakeFiles/os_cw_test.dir/clean:
	cd /d C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\test && $(CMAKE_COMMAND) -P CMakeFiles\os_cw_test.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/os_cw_test.dir/clean

test/CMakeFiles/os_cw_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\test C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\test C:\Users\Asus\Desktop\Coding\CPP\CourseWorkOpS\build\test\CMakeFiles\os_cw_test.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/os_cw_test.dir/depend

