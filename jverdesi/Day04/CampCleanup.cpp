//
// Created by jacob on 12/3/2022.
//
#include <cstring>
#include <string>
#include <list>
#include <iostream>
#include "../Utils/InitDay.h"
#include "CampCleanup.h"

using namespace std;

void day4Part1(const list<string> &inputStringList) {
    int containCount = 0;
    for (string line: inputStringList) {
        if (!line.empty()) {

            int p1Min=stoi(strtok(line.data(),"-"));
            int p1Max=stoi(strtok(nullptr,","));
            int p2Min=stoi(strtok(nullptr,"-"));
            int p2Max=stoi(strtok(nullptr," "));
            if(p1Min<=p2Min and p1Max>=p2Max or p1Min>=p2Min and p1Max<=p2Max){
                containCount+=1;
            }

        }
     }
    cout << "Fully contain pairs: " << containCount << "\n";

}

void day4Part2(const list<string> &inputStringList) {
    int score = 0;
    for (string line: inputStringList) {
        if (!line.empty()) {

            int p1Min=stoi(strtok(line.data(),"-"));
            int p1Max=stoi(strtok(nullptr,","));
            int p2Min=stoi(strtok(nullptr,"-"));
            int p2Max=stoi(strtok(nullptr," "));
            if(p1Min<=p2Max and p1Max>=p2Min or p1Min>=p2Max and p1Max<=p2Min){
                score+=1;
            }

        }
    }
    cout << "Overlapping pairs: " << score << "\n";
}

int mainDay4() {
    initDay(4, &day4Part1, &day4Part2);
    return 0;
}