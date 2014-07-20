project(moa)
cmake_minimum_required(VERSION 3.0)
find_package(GTest REQUIRED)
find_package (Threads)

# include_directories(${GTEST_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-c++1y-extensions -std=c++11")
add_executable(ut
  code.cpp
  ut/tests.cpp
  )

include_directories(${CMAKE_SOURCE_DIR})
target_link_libraries(ut ${GTEST_MAIN_LIBRARY})
target_link_libraries(ut ${GTEST_LIBRARY})
target_link_libraries(ut pthread)
