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
include Applications/Incremental/CMakeFiles/prep-data.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Applications/Incremental/CMakeFiles/prep-data.dir/compiler_depend.make

# Include the progress variables for this target.
include Applications/Incremental/CMakeFiles/prep-data.dir/progress.make

# Include the compile flags for this target's objects.
include Applications/Incremental/CMakeFiles/prep-data.dir/flags.make

Applications/Incremental/CMakeFiles/prep-data.dir/Prep-Data.cpp.o: Applications/Incremental/CMakeFiles/prep-data.dir/flags.make
Applications/Incremental/CMakeFiles/prep-data.dir/Prep-Data.cpp.o: ../Applications/Incremental/Prep-Data.cpp
Applications/Incremental/CMakeFiles/prep-data.dir/Prep-Data.cpp.o: Applications/Incremental/CMakeFiles/prep-data.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Applications/Incremental/CMakeFiles/prep-data.dir/Prep-Data.cpp.o"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/Incremental && /opt/cray/pe/craype/2.7.32/bin/CC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Applications/Incremental/CMakeFiles/prep-data.dir/Prep-Data.cpp.o -MF CMakeFiles/prep-data.dir/Prep-Data.cpp.o.d -o CMakeFiles/prep-data.dir/Prep-Data.cpp.o -c /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/Incremental/Prep-Data.cpp

Applications/Incremental/CMakeFiles/prep-data.dir/Prep-Data.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/prep-data.dir/Prep-Data.cpp.i"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/Incremental && /opt/cray/pe/craype/2.7.32/bin/CC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/Incremental/Prep-Data.cpp > CMakeFiles/prep-data.dir/Prep-Data.cpp.i

Applications/Incremental/CMakeFiles/prep-data.dir/Prep-Data.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/prep-data.dir/Prep-Data.cpp.s"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/Incremental && /opt/cray/pe/craype/2.7.32/bin/CC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/Incremental/Prep-Data.cpp -o CMakeFiles/prep-data.dir/Prep-Data.cpp.s

# Object files for target prep-data
prep__data_OBJECTS = \
"CMakeFiles/prep-data.dir/Prep-Data.cpp.o"

# External object files for target prep-data
prep__data_EXTERNAL_OBJECTS =

Applications/Incremental/prep-data: Applications/Incremental/CMakeFiles/prep-data.dir/Prep-Data.cpp.o
Applications/Incremental/prep-data: Applications/Incremental/CMakeFiles/prep-data.dir/build.make
Applications/Incremental/prep-data: libCombBLAS.a
Applications/Incremental/prep-data: /opt/cray/pe/libsci/24.07.0/GNU/12.3/x86_64/lib/libsci_gnu_mpi_mp.so
Applications/Incremental/prep-data: /opt/cray/pe/libsci/24.07.0/GNU/12.3/x86_64/lib/libsci_gnu_mp.so
Applications/Incremental/prep-data: /usr/lib64/gcc/x86_64-suse-linux/13/libgomp.so
Applications/Incremental/prep-data: usort/libUsortlib.a
Applications/Incremental/prep-data: graph500-1.2/generator/libGraphGenlib.a
Applications/Incremental/prep-data: Applications/Incremental/CMakeFiles/prep-data.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable prep-data"
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/Incremental && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prep-data.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Applications/Incremental/CMakeFiles/prep-data.dir/build: Applications/Incremental/prep-data
.PHONY : Applications/Incremental/CMakeFiles/prep-data.dir/build

Applications/Incremental/CMakeFiles/prep-data.dir/clean:
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/Incremental && $(CMAKE_COMMAND) -P CMakeFiles/prep-data.dir/cmake_clean.cmake
.PHONY : Applications/Incremental/CMakeFiles/prep-data.dir/clean

Applications/Incremental/CMakeFiles/prep-data.dir/depend:
	cd /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/Incremental /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/Incremental /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/Incremental/CMakeFiles/prep-data.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Applications/Incremental/CMakeFiles/prep-data.dir/depend

