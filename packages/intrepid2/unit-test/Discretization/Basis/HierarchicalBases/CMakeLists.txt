FILE(GLOB TEST_SOURCES "*.cpp")

 TRIBITS_ADD_EXECUTABLE_AND_TEST(
   Hierarchical_Basis_Tests
   SOURCES ${TEST_SOURCES}
   ARGS 
   NUM_MPI_PROCS 1
   PASS_REGULAR_EXPRESSION "TEST PASSED"
   ADD_DIR_TO_NAME
   )
