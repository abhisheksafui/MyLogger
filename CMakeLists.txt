cmake_minimum_required(VERSION 3.1)
project(mylogger)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/out/bin)

set(LOGGER_LIB_NAME mylogger)
add_library(${LOGGER_LIB_NAME} STATIC ${PROJECT_SOURCE_DIR}/src/MyLogger.cpp)

target_link_libraries(${LOGGER_LIB_NAME} PRIVATE PocoFoundation)
target_include_directories(${LOGGER_LIB_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src")

add_subdirectory(test)

install(TARGETS ${LOGGER_LIB_NAME} DESTINATION lib)
install(FILES ${PROJECT_SOURCE_DIR}/src/MyLogger.h DESTINATION include)
