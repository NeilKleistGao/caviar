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

add_executable(caviar main.cc caviar.cc fsd.cc fsd.h)

if (BUILD_TEST)
  add_executable(diff_tests tests/diff_tests.cc caviar.cc fsd.cc fsd.h)
  target_link_libraries(diff_tests ${GTEST_BOTH_LIBRARIES})
  target_link_libraries(diff_tests ${CMAKE_THREAD_LIBS_INIT})
endif()
