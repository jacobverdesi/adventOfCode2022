#include <string>
#include <list>
#include <iostream>
#include "../Utils/FileReader.h"
#include "RockPaperScissors.h"

int getScore(const std::list<std::string> &inputStringList) {
    int totalScore = 0;
    for (const std::string &line: inputStringList) {
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
    return totalScore;
}
int getScore2(const std::list<std::string> &inputStringList) {
    int totalScore = 0;
    for (const std::string &line: inputStringList) {
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
    return totalScore;
}

int mainDay2() {
    std::list<std::string> inputStringList = readInputFile("../Data/inputDay2.txt");
    //printStringList(modifyRPSGame(inputStringList));
    int score = getScore(inputStringList);
    std::cout << "Part1 Score: " << score << "\n";
    int score2 = getScore2(inputStringList);
    std::cout << "Part2 Score: " << score2 << "\n";

    return 0;
}
