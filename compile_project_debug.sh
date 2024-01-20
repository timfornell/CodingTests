#!/bin/bash

g++ -o main.exe -g $(find . -name "*.cpp" -o -name "*.hpp")
# g++ -I../TestFramework -o output_file_name $(find . -name "*.cpp" -o -name "*.hpp")
