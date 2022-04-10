#!/bin/bash

if [[ -z $BUILD_TYPE ]]; then
    BUILD_TYPE=Release
fi
echo Running rsa_100 with BUILD_TYPE=$BUILD_TYPE

cd ./build/$BUILD_TYPE/
./Rsa100
cd ..

