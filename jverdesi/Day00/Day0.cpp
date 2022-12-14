//
// Created by jacob on 12/4/2022.
//
#include <string>
#include <list>
#include <iostream>
#include "../Utils/InitDay.h"
#include "Day0.h"

using namespace std;


void day0Part1(const list<string> &inputStringList) {
    int score = 0;
    for (const string &line: inputStringList) {
        if (!line.empty()) {

        }
    }
    cout << "Score: " << score << "\n";

}

void day0Part2(const list<string> &inputStringList) {
    int score = 0;
    for (const string &line: inputStringList) {
        if (!line.empty()) {

        }
    }
    cout << "Score: " << score << "\n";
}

int mainDay0() {
    initDay(0, &day0Part1, &day0Part2);
    return 0;
}