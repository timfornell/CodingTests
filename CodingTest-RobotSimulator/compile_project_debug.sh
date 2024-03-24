#!/bin/bash

g++ --std=c++11 -o main.exe -g main.cpp doctest.hpp $(find Utils -name "*.cpp" -o -name "*.hpp") $(find Robot -name "*.cpp" -o -name "*.hpp") $(find TableTop -name "*.cpp" -o -name "*.hpp")
