#!/bin/bash

if [[ -z $BUILD_TYPE ]]; then
    BUILD_TYPE=Debug
fi
echo Running tests with BUILD_TYPE=$BUILD_TYPE

cd ./build/$BUILD_TYPE/
./TestLargeInts $@
cd ../..

if [[ $BUILD_TYPE -eq "Debug" ]]; then
    if [[ -z $COVERAGE_PERCENT ]]; then
        COVERAGE_PERCENT=0
    fi
    echo "Generating coverage report with percent $COVERAGE_PERCENT"
    mkdir -p build/coverage/html
    gcovr -s -r . --html --html-details -o build/coverage/html/index.html  --fail-under-line $COVERAGE_PERCENT
fi