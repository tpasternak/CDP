project(moa)
cmake_minimum_required(VERSION 3.0)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

find_path(OpenCL_INC
  NAMES "CL/cl.h"
  PATHS "$ENV{AMDAPPSDKROOT}/include"
)
message("-- Found OpenCL include path: ${OpenCL_INC}")

find_library(OpenCL_LIB
  NAMES "OpenCL"
  PATHS "$ENV{AMDAPPSDKROOT}/lib/x86_64"
)
message("-- Found OpenCL libs: ${OpenCL_LIB}")

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
  FileVideo.cpp
  FileVideo.h
  Vienna.cpp
  Vienna.h
  main.cpp
)
target_link_libraries(moa ${OpenCV_LIBS})
target_link_libraries(moa ${OpenCL_LIB})
target_link_libraries(moa ${Boost_PROGRAM_OPTIONS_LIBRARY})
target_link_libraries(moa  /home/tomasz/Projects/viennacl-dev/build/libviennacl/libviennacl.so)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${OpenCL_INC})

