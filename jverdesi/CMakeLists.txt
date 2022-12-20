cmake_minimum_required(VERSION 3.24)
project(AdventOfCode22)

set(CMAKE_CXX_STANDARD 23)

add_executable(AdventOfCode22
        main.cpp
        main.h

        Utils/FileReader.cpp
        Utils/FileReader.h
        Utils/InitDay.cpp
        Utils/InitDay.h
        Utils/StackHelper.cpp
        Utils/StackHelper.h
        Day00/Day0.cpp
        Day00/Day0.h
        Day01/CalorieCounting.cpp
        Day01/CalorieCounting.h
        Day02/RockPaperScissors.cpp
        Day02/RockPaperScissors.h
        Day03/RucksackReorganization.cpp
        Day03/RucksackReorganization.h
        Day04/CampCleanup.cpp
        Day04/CampCleanup.h
        Day05/SupplyStacks.cpp
        Day05/SupplyStacks.h
        Day06/TuningTrouble.cpp
        Day06/TuningTrouble.h
        Day07/NoSpaceLeftOnDevice.cpp
        Day07/NoSpaceLeftOnDevice.h
        Day08/TreetopTreeHouse.cpp
        Day08/TreetopTreeHouse.h
        Day09/RopeBridge.cpp
        Day09/RopeBridge.h
        Day10/CathodeRayTube.cpp
        Day10/CathodeRayTube.h
        Day11/MonkeyInTheMiddle.cpp
        Day11/MonkeyInTheMiddle.h Day09/RopeBridge.cpp Day12/HillClimbAlgorithm.cpp Day12/HillClimbAlgorithm.h Utils/ColorMod.cpp Utils/ColorMod.h Day13/DistressSignal.cpp Day13/DistressSignal.h)