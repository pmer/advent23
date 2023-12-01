#!/bin/bash
mkdir -p build
cd $_
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug && ninja
