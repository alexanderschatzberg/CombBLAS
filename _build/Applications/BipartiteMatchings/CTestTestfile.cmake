# CMake generated Testfile for 
# Source directory: /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/BipartiteMatchings
# Build directory: /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/BipartiteMatchings
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(BPML_Test "/usr/bin/srun" "-n" "4" "/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/BipartiteMatchings/bpml" "er" "12" "8")
set_tests_properties(BPML_Test PROPERTIES  _BACKTRACE_TRIPLES "/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/BipartiteMatchings/CMakeLists.txt;13;ADD_TEST;/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/BipartiteMatchings/CMakeLists.txt;0;")
add_test(BPMM_Test "/usr/bin/srun" "-n" "4" "/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/BipartiteMatchings/bpmm" "er" "12" "8")
set_tests_properties(BPMM_Test PROPERTIES  _BACKTRACE_TRIPLES "/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/BipartiteMatchings/CMakeLists.txt;14;ADD_TEST;/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/BipartiteMatchings/CMakeLists.txt;0;")
