cmake_minimum_required(VERSION 3.1)
project(mylogger)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/out/bin)

add_library(liblogger STATIC ${PROJECT_SOURCE_DIR}/src/MyLogger.cpp)

target_link_libraries(liblogger PUBLIC PocoFoundation)
target_include_directories(liblogger PUBLIC "${PROJECT_SOURCE_DIR}/src")

add_executable(loggertest ${PROJECT_SOURCE_DIR}/test/main.cpp)
target_link_libraries(loggertest liblogger)
