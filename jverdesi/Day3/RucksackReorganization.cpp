//
// Created by jacob on 12/3/2022.
//
#include <string>
#include <bitset>
#include <list>
#include <iostream>
#include "../Utils/FileReader.h"
#include "RucksackReorganization.h"

int64_t uniqueTypes(const std::string &inputString) {
    int64_t unique_type = 0;
    for (auto &ch: inputString) {
        if (ch >= 97)
            unique_type |= 1LL << (ch - 97);
        else
            unique_type |= 1LL << (ch - 39);
    }
    return unique_type;
}

int getSingleBitIndex(int64_t input) {
    int idx = 0;
    while (input) {
        input = input >> 1;
        idx++;
    }
    return idx;
}

int getSumPriorities(const std::list<std::string> &inputStringList) {
    int totalPriority = 0;
    for (const std::string &line: inputStringList) {
        if (!line.empty()) {
            size_t rutsackSize = line.size();
            int64_t container1 = uniqueTypes(line.substr(0, rutsackSize / 2));
            int64_t container2 = uniqueTypes(line.substr(rutsackSize / 2, rutsackSize + 1));
            int64_t duplicate_types = container1 & container2;
            totalPriority += getSingleBitIndex(duplicate_types);
        }
    }
    return totalPriority;
}

int getSumPrioritiesBadge(const std::list<std::string> &inputStringList) {
    int totalPriority = 0;
    int groupIdx = 0;
    int64_t groupTypes[3];
    for (const std::string &line: inputStringList) {
        if (!line.empty()) {
            groupTypes[groupIdx] = uniqueTypes(line);
            groupIdx++;
            if (groupIdx == 3) {
                int64_t duplicate_types = groupTypes[0] & groupTypes[1] & groupTypes[2];
                totalPriority += getSingleBitIndex(duplicate_types);
                std::fill_n(groupTypes, 3, 0);
                groupIdx=0;
            }
        }
    }
    return totalPriority;
}

int mainDay3() {
    std::list<std::string> inputStringList = readInputFile("../Data/inputDay3.txt");
    //printStringList(inputStringList);
    std::cout << "Part1 Score: " << getSumPriorities(inputStringList) << "\n";
    std::cout << "Part2 Score: " << getSumPrioritiesBadge(inputStringList) << "\n";
}