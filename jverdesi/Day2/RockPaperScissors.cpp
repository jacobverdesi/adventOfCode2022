#include <string>
#include <list>
#include <iostream>
#include "RockPaperScissors.h"
#include "../Utils/InitDay.h"
using namespace std;

void getScore(const list<string> &inputStringList) {
    int totalScore = 0;
    for (const string &line: inputStringList) {
        if (!line.empty()) {
            unsigned char p1 = line[0] - 65;
            unsigned char p2 = line[2] - 65 - 23;
            totalScore += p2 + 1;
            if (p1 == p2) {
                totalScore += 3;
            } else if ((p2 + 2) % 3 == p1) {
                totalScore += 6;
            }
        }
    }
    cout << "RPS Score: " << totalScore << "\n";

}
void getScore2(const list<string> &inputStringList) {
    int totalScore = 0;
    for (const string &line: inputStringList) {
        if (!line.empty()) {
            unsigned char p1 = line[0] - 65;
            unsigned char p2 = line[2] -88;
            totalScore += p2 * 3;
            switch(p2){
                case 0:
                    totalScore+=(p1+2)%3+1;
                    break;
                case 1:
                    totalScore+=p1+1;
                    break;
                case 2:
                    totalScore+=(p1+1)%3+1;
                    break;
                default:
                    break;
            }
        }
    }
    cout << "RPS Score: " << totalScore << "\n";
}

int mainDay2() {
    initDay(2,&getScore,&getScore2);
    return 0;
}
