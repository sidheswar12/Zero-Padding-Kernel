cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link pixelsumtest with what we want to test and the GTest and pthread library
add_executable(pixelsumtest pixelsumtest.cpp)
target_link_libraries(pixelsumtest ${GTEST_LIBRARIES} pthread)