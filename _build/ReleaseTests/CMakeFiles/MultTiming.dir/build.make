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
include ReleaseTests/CMakeFiles/MultTiming.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include ReleaseTests/CMakeFiles/MultTiming.dir/compiler_depend.make

# Include the progress variables for this target.
include ReleaseTests/CMakeFiles/MultTiming.dir/progress.make

# Include the compile flags for this target's objects.
include ReleaseTests/CMakeFiles/MultTiming.dir/flags.make

ReleaseTests/CMakeFiles/MultTiming.dir/MultTiming.cpp.o: ReleaseTests/CMakeFiles/MultTiming.dir/flags.make
ReleaseTests/CMakeFiles/MultTiming.dir/MultTiming.cpp.o: ../ReleaseTests/MultTiming.cpp
ReleaseTests/CMakeFiles/MultTiming.dir/MultTiming.cpp.o: ReleaseTests/CMakeFiles/MultTiming.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ReleaseTests/CMakeFiles/MultTiming.dir/MultTiming.cpp.o"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/ReleaseTests && /opt/cray/pe/craype/2.7.32/bin/CC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ReleaseTests/CMakeFiles/MultTiming.dir/MultTiming.cpp.o -MF CMakeFiles/MultTiming.dir/MultTiming.cpp.o.d -o CMakeFiles/MultTiming.dir/MultTiming.cpp.o -c /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/ReleaseTests/MultTiming.cpp

ReleaseTests/CMakeFiles/MultTiming.dir/MultTiming.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MultTiming.dir/MultTiming.cpp.i"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/ReleaseTests && /opt/cray/pe/craype/2.7.32/bin/CC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/ReleaseTests/MultTiming.cpp > CMakeFiles/MultTiming.dir/MultTiming.cpp.i

ReleaseTests/CMakeFiles/MultTiming.dir/MultTiming.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MultTiming.dir/MultTiming.cpp.s"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/ReleaseTests && /opt/cray/pe/craype/2.7.32/bin/CC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/ReleaseTests/MultTiming.cpp -o CMakeFiles/MultTiming.dir/MultTiming.cpp.s

# Object files for target MultTiming
MultTiming_OBJECTS = \
"CMakeFiles/MultTiming.dir/MultTiming.cpp.o"

# External object files for target MultTiming
MultTiming_EXTERNAL_OBJECTS =

ReleaseTests/MultTiming: ReleaseTests/CMakeFiles/MultTiming.dir/MultTiming.cpp.o
ReleaseTests/MultTiming: ReleaseTests/CMakeFiles/MultTiming.dir/build.make
ReleaseTests/MultTiming: libCombBLAS.a
ReleaseTests/MultTiming: /opt/cray/pe/libsci/24.07.0/GNU/12.3/x86_64/lib/libsci_gnu_mpi_mp.so
ReleaseTests/MultTiming: /opt/cray/pe/libsci/24.07.0/GNU/12.3/x86_64/lib/libsci_gnu_mp.so
ReleaseTests/MultTiming: /usr/lib64/gcc/x86_64-suse-linux/13/libgomp.so
ReleaseTests/MultTiming: usort/libUsortlib.a
ReleaseTests/MultTiming: graph500-1.2/generator/libGraphGenlib.a
ReleaseTests/MultTiming: ReleaseTests/CMakeFiles/MultTiming.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MultTiming"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/ReleaseTests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MultTiming.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ReleaseTests/CMakeFiles/MultTiming.dir/build: ReleaseTests/MultTiming
.PHONY : ReleaseTests/CMakeFiles/MultTiming.dir/build

ReleaseTests/CMakeFiles/MultTiming.dir/clean:
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/ReleaseTests && $(CMAKE_COMMAND) -P CMakeFiles/MultTiming.dir/cmake_clean.cmake
.PHONY : ReleaseTests/CMakeFiles/MultTiming.dir/clean

ReleaseTests/CMakeFiles/MultTiming.dir/depend:
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/ReleaseTests /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/ReleaseTests /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/ReleaseTests/CMakeFiles/MultTiming.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ReleaseTests/CMakeFiles/MultTiming.dir/depend

