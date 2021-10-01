project(LargeIntegersArithmetics CXX)
cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB LargeIntsSrcs "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB LargeIntsIncludes "${PROJECT_SOURCE_DIR}/include")

add_library(LargeInts STATIC ${LargeIntsSrcs})
target_include_directories(LargeInts PUBLIC ${LargeIntsIncludes})

find_package(GTest REQUIRED)
include(GoogleTest)
file(GLOB TestLargeIntsSrcs "${PROJECT_SOURCE_DIR}/tests/*.cpp")
add_executable(TestLargeInts ${TestLargeIntsSrcs})
target_include_directories(TestLargeInts PUBLIC ${LargeIntsIncludes})
target_link_libraries(TestLargeInts LargeInts gtest gtest_main pthread)
gtest_discover_tests(TestLargeInts)