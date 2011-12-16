#testing

add_executable(openTest
  openTest.cxx
)

add_executable(fileSizeTest
  fileSizeTest.cxx
)

add_executable(constructorTest
  constructorTest.cxx
)

#copy the test file to the build directory so tests can pass
configure_file(test.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_test(openTest ${CMAKE_CURRENT_BINARY_DIR}/openTest)
add_test(fileSizeTest ${CMAKE_CURRENT_BINARY_DIR}/fileSizeTest)
add_test(constructorTest ${CMAKE_CURRENT_BINARY_DIR}/constructorTest)

