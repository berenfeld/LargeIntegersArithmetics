./bin/bash

if [[ -z $BUILD_TYPE ]]; then
    BUILD_TYPE=Debug
fi
echo Running tests with BUILD_TYPE=$BUILD_TYPE

mkdir -p build/$BUILD_TYPE/coverage/html
./build/$BUILD_TYPE/TestLargeInts $@
gcovr -s -r . --html --html-details -o build/$BUILD_TYPE/coverage/html/index.html
