cmake_minimum_required(VERSION 3.5)

project(out.o LANGUAGES CXX)

find_package(OpenCV REQUIRED)

include_directories( ${OPENCV_INCLUDE_DIRS} )

FILE(GLOB SRC_FILES "*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS})