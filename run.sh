#!/bin/bash

mkdir -p build
cd build
qmake6 ../qmeetapp.pro
make
./qmeetapp
