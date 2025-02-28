# CMake generated Testfile for 
# Source directory: /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/SpMSpV-IPDPS2017
# Build directory: /global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/SpMSpV-IPDPS2017
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(SpMSpVBench_test "/usr/bin/srun" "-n" "4" "/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/_build/Applications/SpMSpV-IPDPS2017/SpMSpVBench" "-rmat" "18")
set_tests_properties(SpMSpVBench_test PROPERTIES  _BACKTRACE_TRIPLES "/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/SpMSpV-IPDPS2017/CMakeLists.txt;8;ADD_TEST;/global/homes/a/afs223/Desktop/SpGEMM-Profiling/ext/CombBLAS/Applications/SpMSpV-IPDPS2017/CMakeLists.txt;0;")
