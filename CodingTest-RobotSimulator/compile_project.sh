#!/bin/bash

 g++ -o main.exe main.cpp doctest.hpp $(find Utils -name "*.cpp" -o -name "*.hpp") $(find Robot -name "*.cpp" -o -name "*.hpp") $(find TableTop -name "*.cpp" -o -name "*.hpp")