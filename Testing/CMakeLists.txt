#testing
add_executable(statSizeTest
  statSizeTest.cxx
)

add_executable(openTest
  openTest.cxx
)

add_executable(fileSizeTest
  fileSizeTest.cxx
)

add_test(statSizeTest ${CMAKE_CURRENT_BINARY_DIR}/statSizeTest)
add_test(openTest ${CMAKE_CURRENT_BINARY_DIR}/openTest)
add_test(fileSizeTest ${CMAKE_CURRENT_BINARY_DIR}/fileSizeTest)


