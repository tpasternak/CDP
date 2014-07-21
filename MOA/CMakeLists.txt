project(moa)
cmake_minimum_required(VERSION 3.0)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-c++1y-extensions -std=c++11")

add_executable(ut
  Mapping.cpp
  Mapping.h
  ut/tests.cpp
  )
target_link_libraries(ut ${GTEST_MAIN_LIBRARY})
target_link_libraries(ut ${GTEST_LIBRARY})
target_link_libraries(ut pthread)

add_executable(moa
  Mapping.cpp
  Mapping.h
  Calibration.cpp
  Calibration.h
  main.cpp
)
target_link_libraries(moa ${OpenCV_LIBS})
target_link_libraries(moa ${Boost_PROGRAM_OPTIONS_LIBRARY})
message(${Boost_PROGRAM_OPTIONS_LIBRARY})

include_directories(${CMAKE_SOURCE_DIR})

