# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build

# Include any dependencies generated for this target.
include ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/compiler_depend.make

# Include the progress variables for this target.
include ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/progress.make

# Include the compile flags for this target's objects.
include ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/flags.make

ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.o: ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/flags.make
ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.o: ../ReleaseTests/SpGEMM3DTest.cpp
ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.o: ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.o"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/ReleaseTests && /opt/cray/pe/craype/2.7.32/bin/CC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.o -MF CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.o.d -o CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.o -c /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/ReleaseTests/SpGEMM3DTest.cpp

ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.i"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/ReleaseTests && /opt/cray/pe/craype/2.7.32/bin/CC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/ReleaseTests/SpGEMM3DTest.cpp > CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.i

ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.s"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/ReleaseTests && /opt/cray/pe/craype/2.7.32/bin/CC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/ReleaseTests/SpGEMM3DTest.cpp -o CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.s

# Object files for target SpGEMM3DTest
SpGEMM3DTest_OBJECTS = \
"CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.o"

# External object files for target SpGEMM3DTest
SpGEMM3DTest_EXTERNAL_OBJECTS =

ReleaseTests/SpGEMM3DTest: ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/SpGEMM3DTest.cpp.o
ReleaseTests/SpGEMM3DTest: ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/build.make
ReleaseTests/SpGEMM3DTest: libCombBLAS.a
ReleaseTests/SpGEMM3DTest: /opt/cray/pe/libsci/24.07.0/GNU/12.3/x86_64/lib/libsci_gnu_mpi_mp.so
ReleaseTests/SpGEMM3DTest: /opt/cray/pe/libsci/24.07.0/GNU/12.3/x86_64/lib/libsci_gnu_mp.so
ReleaseTests/SpGEMM3DTest: /usr/lib64/gcc/x86_64-suse-linux/13/libgomp.so
ReleaseTests/SpGEMM3DTest: usort/libUsortlib.a
ReleaseTests/SpGEMM3DTest: graph500-1.2/generator/libGraphGenlib.a
ReleaseTests/SpGEMM3DTest: ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SpGEMM3DTest"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/ReleaseTests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SpGEMM3DTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/build: ReleaseTests/SpGEMM3DTest
.PHONY : ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/build

ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/clean:
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/ReleaseTests && $(CMAKE_COMMAND) -P CMakeFiles/SpGEMM3DTest.dir/cmake_clean.cmake
.PHONY : ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/clean

ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/depend:
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/ReleaseTests /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/ReleaseTests /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ReleaseTests/CMakeFiles/SpGEMM3DTest.dir/depend

