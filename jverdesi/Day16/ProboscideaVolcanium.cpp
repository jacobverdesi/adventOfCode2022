//
// Created by jverdesi on 12/25/22.
//

#include "ProboscideaVolcanium.h"

#include <string>
#include <list>
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <regex>
#include "../Utils/InitDay.h"

using namespace std;

class Valve {

    int flowRate = -1;
    vector<int> tunnelTo;
public:
    int valveNum;
    string valveChar;
    explicit Valve(string line) {
        const regex re(R"([A-Z]{2}|\d+)");

        smatch match;
        int i = 0;
        while (regex_search(line, match, re)) {
            string val=match.str();
            if(i==0){
                valveChar=val;
                valveNum=val[1]-65;
                valveNum+=(val[0]-65)*27;

            }
            else if(i==1){
                flowRate=stoi(val);
            }
            else{
                int tunnelNum=0;
                tunnelNum=val[1]-65;
                tunnelNum+=(val[0]-65)*27;
                tunnelTo.push_back(tunnelNum);
            }

            i++;
            line = match.suffix().str();
        }
    }

};

class ProboscideaVolcanium {
private:
    map<int,Valve> valveMap;


public:
    explicit ProboscideaVolcanium(const list<string> &inputStringList, bool isPart2 = false) {
        for (const string& line: inputStringList) {
            Valve v=Valve(line);
            valveMap.insert(make_pair(v.valveNum,v));
        }
    }
};

void day16Part1(const list<string> &inputStringList) {
    ProboscideaVolcanium proboscideaVolcanium = ProboscideaVolcanium(inputStringList);
//    cout << "Score: " << score << "\n";

}

void day16Part2(const list<string> &inputStringList) {
    int score = -1;
    for (const string &line: inputStringList) {
        if (!line.empty()) {

        }
    }
    cout << "Score: " << score << "\n";
}

int mainDay16() {
    initDay(16, &day16Part1, &day16Part2);
    return 16;
}