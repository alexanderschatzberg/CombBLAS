#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "CombBLAS::Usortlib" for configuration ""
set_property(TARGET CombBLAS::Usortlib APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(CombBLAS::Usortlib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libUsortlib.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS CombBLAS::Usortlib )
list(APPEND _IMPORT_CHECK_FILES_FOR_CombBLAS::Usortlib "${_IMPORT_PREFIX}/lib/libUsortlib.a" )

# Import target "CombBLAS::GraphGenlib" for configuration ""
set_property(TARGET CombBLAS::GraphGenlib APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(CombBLAS::GraphGenlib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libGraphGenlib.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS CombBLAS::GraphGenlib )
list(APPEND _IMPORT_CHECK_FILES_FOR_CombBLAS::GraphGenlib "${_IMPORT_PREFIX}/lib/libGraphGenlib.a" )

# Import target "CombBLAS::CombBLAS" for configuration ""
set_property(TARGET CombBLAS::CombBLAS APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(CombBLAS::CombBLAS PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C;CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libCombBLAS.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS CombBLAS::CombBLAS )
list(APPEND _IMPORT_CHECK_FILES_FOR_CombBLAS::CombBLAS "${_IMPORT_PREFIX}/lib/libCombBLAS.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
