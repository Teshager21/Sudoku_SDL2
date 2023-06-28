cmake_minimum_required(VERSION 3.10)

project(tests)

#add_subdirectory(googletest)

# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(${PROJECT_NAME} test.cpp)

# target_link_libraries(runTests gtest gtest_main)    