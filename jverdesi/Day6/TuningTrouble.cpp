//
// Created by jacob on 12/4/2022.
//
#include <string>
#include <list>
#include <iostream>
#include <map>
#include "../Utils/InitDay.h"
#include "TuningTrouble.h"

using namespace std;
bool hasDuplicate(const char* inputString,int size){
    map<char,int> count;
    for (int i=0;i<size;i++) {
        count[inputString[i]]++;
    }
    return any_of(count.begin(),count.end(), [](const auto& p) { return p.second>1; });

}
int findMarkerIndex(const list<string> &inputStringList,const int width){
    int idx = 0;
    for (const string& line: inputStringList) {
        if (!line.empty()) {
            char buffer[width];
            line.copy(buffer,width,idx);
            while (hasDuplicate(buffer,width)){
                line.copy(buffer,width,idx);
                idx++;
            }
        }
    }
    return idx;
}
void day6Part1(const list<string> &inputStringList) {
    const int width=4;
    cout << "First start-of-packet index: " << findMarkerIndex(inputStringList,width)+width-1 << "\n";

}

void day6Part2(const list<string> &inputStringList) {
    const int width=14;
    cout << "First start-of-Message index: " << findMarkerIndex(inputStringList,width)+width-1 << "\n";
}

int mainDay6() {
    initDay(6, &day6Part1, &day6Part2);
    return 0;
}