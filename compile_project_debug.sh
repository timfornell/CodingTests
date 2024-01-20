#!/bin/bash

g++ --std=c++11 -o main.exe -g $(find . -name "*.cpp" -o -name "*.hpp")
