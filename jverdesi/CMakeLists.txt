cmake_minimum_required(VERSION 3.24)
project(AdventOfCode22)

set(CMAKE_CXX_STANDARD 23)

add_executable(AdventOfCode22 main.cpp Utils/FileReader.cpp Utils/FileReader.h main.h main.cpp main.h Day1/MaxElfCalories.cpp Day1/MaxElfCalories.h Day2/RPS.cpp Day2/RPS.h)