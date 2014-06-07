cmake_minimum_required(VERSION 2.8)
project(hello)
add_executable(hello main.cpp ${CMAKE_BINARY_DIR}/generated/MainWindowBase.cpp)
aux_source_directory(. SRC_LIST)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base adv REQUIRED)
include(${wxWidgets_USE_FILE})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
include_directories(${CMAKE_BINARY_DIR}/generated)
set(CMAKE_CXX_FLAGS "-std=c++1y -stdlib=libc++ ${CMAKE_CXX_FLAGS}" )


add_custom_command(
  OUTPUT ${CMAKE_BINARY_DIR}/generated/MainWindowBase.cpp ${CMAKE_BINARY_DIR}/generated/MainWindowBase.h
  COMMAND wxformbuilder ${CMAKE_SOURCE_DIR}/MainWindow.fbp -g && mkdir -p ${CMAKE_BINARY_DIR}/generated/ && mv ${CMAKE_SOURCE_DIR}/MainWindowBase.cpp ${CMAKE_SOURCE_DIR}/MainWindowBase.h ${CMAKE_BINARY_DIR}/generated/
  DEPENDS ${CMAKE_SOURCE_DIR}/MainWindow.fbp 
  COMMENT "WXFORMBUILDER " ${CMAKE_SOURCE_DIR}/MainWindow.fbp 
  VERBATIM
)

