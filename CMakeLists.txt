cmake_minimum_required(VERSION 2.8)
project(hello)
set(SourceFiles 
  main.cpp 
  MainFrame.cpp
  MainFrame.h
  ${CMAKE_BINARY_DIR}/generated/MainWindowBase.cpp
  ${CMAKE_BINARY_DIR}/generated/MainWindowBase.h
)
add_executable(hello ${SourceFiles})

# WxWidgets
aux_source_directory(. SRC_LIST)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base adv REQUIRED)
include(${wxWidgets_USE_FILE})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

# OpenCV
find_package( OpenCV COMPONENTS videostab video highgui core imgproc calib3d REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( hello ${OpenCV_LIBS} )

# General
include_directories(${CMAKE_BINARY_DIR}/generated)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11 -g ${CMAKE_CXX_FLAGS}" )


add_custom_command(
  OUTPUT ${CMAKE_BINARY_DIR}/generated/MainWindowBase.cpp ${CMAKE_BINARY_DIR}/generated/MainWindowBase.h
  COMMAND wxformbuilder ${CMAKE_SOURCE_DIR}/MainWindow.fbp -g && mkdir -p ${CMAKE_BINARY_DIR}/generated/ && mv ${CMAKE_SOURCE_DIR}/MainWindowBase.cpp ${CMAKE_SOURCE_DIR}/MainWindowBase.h ${CMAKE_BINARY_DIR}/generated/
  DEPENDS ${CMAKE_SOURCE_DIR}/MainWindow.fbp 
  COMMENT "WXFORMBUILDER " ${CMAKE_SOURCE_DIR}/MainWindow.fbp 
  VERBATIM
)


set(AllFiles ${SourceFiles} ${HeaderFiles})
string(REPLACE ";" "\n" AllFiles "${AllFiles}")
file(WRITE ${CMAKE_BINARY_DIR}/cscope.files "${AllFiles}")