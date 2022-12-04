cmake_minimum_required(VERSION 3.24)
project(AdventOfCode22)

set(CMAKE_CXX_STANDARD 23)

add_executable(AdventOfCode22 main.cpp Utils/FileReader.cpp Utils/FileReader.h main.h main.cpp main.h Day1/CalorieCounting.cpp Day1/CalorieCounting.h Day2/RockPaperScissors.cpp Day2/RockPaperScissors.h Day3/RucksackReorganization.cpp Day3/RucksackReorganization.h Utils/InitDay.cpp Utils/InitDay.h Day4/CampCleanup.cpp Day4/CampCleanup.h Day0/Day0.cpp Day0/Day0.h Day5/Day5.cpp)