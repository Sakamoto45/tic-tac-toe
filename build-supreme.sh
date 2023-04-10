#!/bin/bash

rm -rf ./build
rm -rf ./dist

mkdir ./build
mkdir ./build/linux
mkdir ./build/windows
mkdir ./dist

(
    cd ./build/linux
    cmake ../../
    make
)

cp ./build/linux/ttt ./dist/

(
    cd ./build/windows
    x86_64-w64-mingw32-cmake ../../
    make
)

cp ./build/windows/ttt.exe ./dist/
