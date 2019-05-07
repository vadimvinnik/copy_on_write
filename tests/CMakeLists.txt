cmake_minimum_required(VERSION 3.8)

project(copy_on_write_tests)

add_executable(${PROJECT_NAME}
  main.cpp
  allocations_test.cpp
  int_array.h
  int_array.cpp
  int_array_test.cpp)

target_link_libraries(${PROJECT_NAME} CONAN_PKG::catch2)

target_include_directories(${PROJECT_NAME} PRIVATE ../include) 

add_test(
  NAME test_all
  COMMAND copy_on_write_tests)

