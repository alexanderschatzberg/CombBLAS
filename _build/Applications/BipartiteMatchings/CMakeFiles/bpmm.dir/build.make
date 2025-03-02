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
include Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/compiler_depend.make

# Include the progress variables for this target.
include Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/progress.make

# Include the compile flags for this target's objects.
include Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/flags.make

Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.o: Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/flags.make
Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.o: ../Applications/BipartiteMatchings/BPMaximumMatching.cpp
Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.o: Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.o"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/BipartiteMatchings && /opt/cray/pe/craype/2.7.32/bin/CC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.o -MF CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.o.d -o CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.o -c /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/BipartiteMatchings/BPMaximumMatching.cpp

Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.i"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/BipartiteMatchings && /opt/cray/pe/craype/2.7.32/bin/CC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/BipartiteMatchings/BPMaximumMatching.cpp > CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.i

Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.s"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/BipartiteMatchings && /opt/cray/pe/craype/2.7.32/bin/CC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/BipartiteMatchings/BPMaximumMatching.cpp -o CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.s

# Object files for target bpmm
bpmm_OBJECTS = \
"CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.o"

# External object files for target bpmm
bpmm_EXTERNAL_OBJECTS =

Applications/BipartiteMatchings/bpmm: Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/BPMaximumMatching.cpp.o
Applications/BipartiteMatchings/bpmm: Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/build.make
Applications/BipartiteMatchings/bpmm: libCombBLAS.a
Applications/BipartiteMatchings/bpmm: /opt/cray/pe/libsci/24.07.0/GNU/12.3/x86_64/lib/libsci_gnu_mpi_mp.so
Applications/BipartiteMatchings/bpmm: /opt/cray/pe/libsci/24.07.0/GNU/12.3/x86_64/lib/libsci_gnu_mp.so
Applications/BipartiteMatchings/bpmm: /usr/lib64/gcc/x86_64-suse-linux/13/libgomp.so
Applications/BipartiteMatchings/bpmm: usort/libUsortlib.a
Applications/BipartiteMatchings/bpmm: graph500-1.2/generator/libGraphGenlib.a
Applications/BipartiteMatchings/bpmm: Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bpmm"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/BipartiteMatchings && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bpmm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/build: Applications/BipartiteMatchings/bpmm
.PHONY : Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/build

Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/clean:
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/BipartiteMatchings && $(CMAKE_COMMAND) -P CMakeFiles/bpmm.dir/cmake_clean.cmake
.PHONY : Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/clean

Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/depend:
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/BipartiteMatchings /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/BipartiteMatchings /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Applications/BipartiteMatchings/CMakeFiles/bpmm.dir/depend

