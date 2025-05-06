cmake_minimum_required(VERSION 3.10)
project(ieee754_converter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Основна програма
include_directories(include)
file(GLOB SRC_FILES "src/*.cpp")
add_executable(ieee754_converter main.cpp ${SRC_FILES})

# Google Test
enable_testing()
add_subdirectory(external/googletest)
include_directories(${gtest_SOURCE_DIR}/include)

file(GLOB TEST_SRC tests/*.cpp)
add_executable(run_tests ${TEST_SRC} ${SRC_FILES})
target_link_libraries(run_tests gtest gtest_main)
add_test(NAME AllTests COMMAND run_tests)
