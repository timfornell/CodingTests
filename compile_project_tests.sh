#!/bin/bash

g++ --std=c++11 -o test.exe $(find Utils -name "*.cpp" -o -name "*.hpp") $(find Robot -name "*.cpp" -o -name "*.hpp") $(find TableTop -name "*.cpp" -o -name "*.hpp") $(find TestFramework -name "*.cpp" -o -name "*.hpp")
