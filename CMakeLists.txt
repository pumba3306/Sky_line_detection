cmake_minimum_required(VERSION 3.5)

project(Sky_line_detection)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
    src/main.cpp
    src/func.cpp
    src/Class.cpp
    src/find_horizon_line.cpp)

set(HEADERS
    include/func.h
    include/Class.h)

add_executable( ${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )

