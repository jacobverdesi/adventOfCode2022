//
// Created by jacob on 12/3/2022.
//
#include <string>
#include <list>
#include <iostream>
#include "RucksackReorganization.h"
#include "../Utils/InitDay.h"
using namespace std;

int64_t uniqueTypes(const string &inputString) {
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

void day3Part1(const list<string> &inputStringList) {
    int totalPriority = 0;
    for (const string &line: inputStringList) {
        if (!line.empty()) {
            size_t rutsackSize = line.size();
            int64_t container1 = uniqueTypes(line.substr(0, rutsackSize / 2));
            int64_t container2 = uniqueTypes(line.substr(rutsackSize / 2, rutsackSize + 1));
            int64_t duplicate_types = container1 & container2;
            totalPriority += getSingleBitIndex(duplicate_types);
        }
    }
    cout << "Sum Priorities: " << totalPriority << "\n";

}

void day3Part2(const list<string> &inputStringList) {
    int totalPriority = 0;
    int groupIdx = 0;
    int64_t groupTypes[3];
    for (const string &line: inputStringList) {
        if (!line.empty()) {
            groupTypes[groupIdx] = uniqueTypes(line);
            groupIdx++;
            if (groupIdx == 3) {
                int64_t duplicate_types = groupTypes[0] & groupTypes[1] & groupTypes[2];
                totalPriority += getSingleBitIndex(duplicate_types);
                fill_n(groupTypes, 3, 0);
                groupIdx=0;
            }
        }
    }
    cout << "Sum Priorities Group of 3: " << totalPriority << "\n";

}

int mainDay3() {
    initDay(3, &day3Part1, &day3Part2);
    return 0;
}