
set(TEST_EXECUTABLE_NAME loggertest)
add_executable(${TEST_EXECUTABLE_NAME} main.cpp)
target_link_libraries(${TEST_EXECUTABLE_NAME} ${LOGGER_LIB_NAME})
