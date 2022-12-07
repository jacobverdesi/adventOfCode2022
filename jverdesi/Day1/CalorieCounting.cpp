//
// Created by jacob on 12/3/2022.
//

#include "CalorieCounting.h"
#include <iostream>
#include <string>
#include <list>
#include "../Utils/InitDay.h"
using namespace std;
void day1Part1(const list<string> &inputStringList) {

    int calorieSum = 0;
    int maxCal = 0;

    for (const string &line: inputStringList) {
        if (!line.empty()) {
            calorieSum += stoi(line);
        } else {
            if (calorieSum > maxCal) {
                maxCal = calorieSum;
            }
            calorieSum = 0;
        }

    }
    cout << "Max Calorie Elf: " << maxCal << '\n';

}

void day1Part2(const list<string> &inputStringList) {
    int calorieSum = 0;
    list<int> callList;
    for (const string &line: inputStringList) {
        if (!line.empty()) {
            calorieSum += stoi(line);
        } else {
            callList.push_back(calorieSum);
            calorieSum = 0;
        }
    }
    callList.sort();
    int max3 = 0;
    for (int i = 0; i < 3; ++i) {
        max3 += callList.back();
        callList.pop_back();
    }
    cout << "Total Calories of 3 top Elfs: " << max3 << '\n';
}

int mainDay1() {
    initDay(1, &day1Part1, &day1Part2);
    return 0;
}
