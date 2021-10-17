project(LargeIntegersArithmetics CXX)
cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# treat warnings as errors
add_compile_options(-Wall -Werror)

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
  target_link_libraries(coverage_config INTERFACE gcov --coverage)
endif(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

file(GLOB LargeIntsSrcs "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB LargeIntsIncludes "${PROJECT_SOURCE_DIR}/include")

add_library(LargeInts STATIC ${LargeIntsSrcs})
target_include_directories(LargeInts PUBLIC ${LargeIntsIncludes})
target_link_libraries(LargeInts PRIVATE coverage_config)

enable_testing()
find_package(GTest REQUIRED)
file(GLOB TestLargeIntsSrcs "${PROJECT_SOURCE_DIR}/tests/*.cpp")
add_executable(TestLargeInts ${TestLargeIntsSrcs})
target_include_directories(TestLargeInts PUBLIC ${LargeIntsIncludes} ${GTEST_INCLUDE_DIRS})
target_link_libraries(TestLargeInts LargeInts ${GTEST_BOTH_LIBRARIES} pthread)
gtest_discover_tests(TestLargeInts AUTO)

# benchmark
find_package(benchmark REQUIRED)
include(${benchmark_CONFIG})
file(GLOB BenchmarkLargeIntsSrcs "${PROJECT_SOURCE_DIR}/benchmarks/*.cpp")
add_executable(BenchmarkLargeInts ${BenchmarkLargeIntsSrcs})
target_include_directories(BenchmarkLargeInts PUBLIC ${LargeIntsIncludes})
target_link_libraries(BenchmarkLargeInts LargeInts benchmark::benchmark)
