project(LargeIntegersArithmetics CXX)
cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Code Coverage Configuration
add_library(coverage_config INTERFACE)

option(CODE_COVERAGE "Enable coverage reporting" ON)
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  # Add required flags (GCC & LLVM/Clang)
  target_compile_options(coverage_config INTERFACE
    -O0        # no optimization
    -g         # generate debug info
    --coverage # sets all required flags
  )
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()
endif(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

file(GLOB LargeIntsSrcs "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB LargeIntsIncludes "${PROJECT_SOURCE_DIR}/include")

add_library(LargeInts STATIC ${LargeIntsSrcs})
target_include_directories(LargeInts PUBLIC ${LargeIntsIncludes})
target_link_libraries(LargeInts PRIVATE coverage_config)

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)
file(GLOB TestLargeIntsSrcs "${PROJECT_SOURCE_DIR}/tests/*.cpp")
add_executable(TestLargeInts ${TestLargeIntsSrcs})
target_include_directories(TestLargeInts PUBLIC ${LargeIntsIncludes})
target_link_libraries(TestLargeInts LargeInts gtest gtest_main pthread)
gtest_discover_tests(TestLargeInts AUTO)
