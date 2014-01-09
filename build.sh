#!/bin/bash

g++ main.cc -O3 -std=c++0x -Wall -Werror -o cache

pushd benchmark
cmake -DCMAKE_BUILD_TYPE=Release .
make -j4
popd

g++ bm.cc -O3 -std=c++0x -Wall -Werror -I benchmark/include -L benchmark/lib -l benchmark -l pthread -o cache_bm
