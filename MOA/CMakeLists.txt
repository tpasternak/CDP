project(moa)
cmake_minimum_required(VERSION 2.8)
find_package(GTest REQUIRED)
find_package (Threads)

# include_directories(${GTEST_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -std=c++11")
add_executable(ut
  code.cpp
  ut/tests.cpp
  )

target_link_libraries(ut ${GTEST_MAIN_LIBRARY})
target_link_libraries(ut ${GTEST_LIBRARY})
target_link_libraries(ut pthread)
