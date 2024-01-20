#!/bin/bash

g++ --std=c++11 -o main.exe $(find . -name "*.cpp" -o -name "*.hpp")
