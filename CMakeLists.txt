cmake_minimum_required(VERSION 3.16)
project(caviar)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

option(BUILD_TEST "build test modules" ON)

if (BUILD_TEST)
  find_package(GTest REQUIRED)
  find_package(Threads REQUIRED)
  include_directories(${GTEST_INCLUDE_DIRS})
endif()

add_executable(caviar main.cc)

if (BUILD_TEST)
  add_executable(diff_test tests/diff_test.cc ${CRIMSON_CORE})
  target_link_libraries(diff_test ${GTEST_BOTH_LIBRARIES})
  target_link_libraries(diff_test ${CMAKE_THREAD_LIBS_INIT})
endif()
