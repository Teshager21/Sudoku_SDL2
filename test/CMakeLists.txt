cmake_minimum_required(VERSION 3.10)

project(tests)

#add_subdirectory(googletest)
add_library(mylib STATIC ../model.cpp ../solver.cpp ../window.cpp ../texture.cpp ../AssetManager.cpp ../GameEntity.cpp ${GTEST_LIBRARIES} )
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(
    ${PROJECT_NAME} 
    test.cpp
    )

target_link_libraries( ${PROJECT_NAME} mylib pthread)    

include(GoogleTest)
gtest_discover_tests(tests)