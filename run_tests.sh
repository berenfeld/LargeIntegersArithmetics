./bin/bash

mkdir -p build/coverage/html
./build/TestLargeInts $@
gcovr -s -r . --html --html-details -o build/coverage/html/index.html
