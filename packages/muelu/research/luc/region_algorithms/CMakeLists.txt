INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../test/unit_tests)

# This test requires Tpetra, so it's only included if Tpetra is enabled
IF (${PACKAGE_NAME}_ENABLE_Tpetra) #AND ${PACKAGE_NAME}_ENABLE_Ifpack2 AND ${PACKAGE_NAME}_ENABLE_Amesos2)

  TRIBITS_ADD_EXECUTABLE(
    RegionsDriver
    SOURCES Driver.cpp
    COMM serial mpi
    )

  TRIBITS_ADD_EXECUTABLE(
    StructuredRegionsDriver
    SOURCES Driver_Structured_Regions.cpp
    COMM serial mpi
    )

  TRIBITS_COPY_FILES_TO_BINARY_DIR(tawiesn_cp
    SOURCE_FILES structured_1dof.xml
    )

ENDIF()

