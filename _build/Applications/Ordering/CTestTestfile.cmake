# CMake generated Testfile for 
# Source directory: /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/Ordering
# Build directory: /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/Ordering
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(RCM_Test "/usr/bin/srun" "-n" "4" "/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/Ordering/rcm" "er" "12")
set_tests_properties(RCM_Test PROPERTIES  _BACKTRACE_TRIPLES "/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/Ordering/CMakeLists.txt;8;ADD_TEST;/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/Ordering/CMakeLists.txt;0;")
