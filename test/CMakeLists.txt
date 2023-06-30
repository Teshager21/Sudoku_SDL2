cmake_minimum_required(VERSION 3.10)

project(tests)

#add_subdirectory(googletest)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(
    ${PROJECT_NAME} 
    test.cpp
    )

target_link_libraries(tests ${GTEST_LIBRARIES} pthread)    

include(GoogleTest)
gtest_discover_tests(tests)