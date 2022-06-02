#!/bin/bash

if [[ -z $BUILD_TYPE ]]; then
    BUILD_TYPE=Release
fi
echo Running benchmark with BUILD_TYPE=$BUILD_TYPE

./build/Release/BenchmarkLargeInts  --benchmark_repetitions=5 --benchmark_report_aggregates_only $@
