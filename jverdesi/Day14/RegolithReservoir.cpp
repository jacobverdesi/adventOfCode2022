//
// Created by jacob on 12/23/21422.
//

#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <regex>
#include "../Utils/InitDay.h"
#include "RegolithReservoir.h"
#include "../Utils/tokenizer.h"

using namespace std;


class CaveCrossSection {
private:
    int width;
    int height;
    int xOffset = 0;
    vector<vector<char>> map;

public:
    explicit CaveCrossSection(const list<string> &inputStringList,bool isPart2= false) {
        vector<int> xList;
        vector<int> yList;
        vector<pair<pair<int, int>, pair<int, int>>> rockLines;
        for (const string &line: inputStringList) {
            if (!line.empty()) {
                const regex arrow(R"(->)");
                const regex comma(R"(,)");

                vector<string> tokenized = tokenize(line, arrow);
                pair<int, int> prevPair;
                int firstPairInitalized = false;
                for (const auto &xyTuple: tokenized) {

                    vector<string> xyPair = tokenize(xyTuple, comma);
                    int x = stoi(xyPair[0]);
                    int y = stoi(xyPair[1]);


                    if (firstPairInitalized) {
                        rockLines.emplace_back(prevPair, make_pair(x, y));
                    }
                    firstPairInitalized = true;
                    prevPair = make_pair(x, y);
                    xList.push_back(x);
                    yList.push_back(y);
                }
            }
        }
        const auto [minX, maxX] = minmax_element(xList.begin(), xList.end());
        const auto [minY, maxY] = minmax_element(yList.begin(), yList.end());

        width = *maxX - *minX + 1;
        height = *maxY + 1;


        xOffset = *minX;
        if(isPart2) {
            height += 2;
            width=height*5;
            xOffset=*minX-width/2;

            rockLines.emplace_back(make_pair(xOffset,height-1), make_pair(xOffset+width-1,height-1));
        }
        map = vector(height, vector(width, '.'));

        for (auto [a, b]: rockLines) {
            if (a.first == b.first) {
                auto [yMin, yMax] = minmax(a.second, b.second);

                for (int y = yMin; y <= yMax; y++) {
                    map[y][a.first - xOffset] = '#';
                }

            } else if (a.second == b.second) {

                auto [xMin, xMax] = minmax(a.first, b.first);

                for (int x = xMin; x <= xMax; x++) {
                    map[a.second][x - xOffset] = '#';
                }
            }

        }

    }

    int placeAllSands() {
        int numPlaced=0;
        while (placeNewSand()) {
            cout<<"Sand Num: "<<numPlaced<<'\n';
            numPlaced++;

            printMap();

        }

        return numPlaced;
    }

    bool placeNewSand() {
        int x = 500 - xOffset;
        int y = 0;

        while (true) {
            if (y + 1 >= height or x-1<0 or x+1>=width)
                return false;
            char left = map[y + 1][x - 1];
            char down = map[y + 1][x];
            char right = map[y + 1][x + 1];

            if (down == '.') {
                y++;
            } else if (left == '.') {
                y++;
                x--;
            } else if (right == '.') {
                y++;
                x++;
            } else break;



        }
        map[y][x]='o';


        return true;


    }

    void printMap() {
        int yIdx = 0;
        for (const auto &row: map) {
            if (yIdx < height)
                cout << yIdx << " ";
            for (auto col: row) {
                cout << col;
            }
            cout << "\n";
            yIdx++;
        }
    }
};


void day14Part1(const list<string> &inputStringList) {
    CaveCrossSection cave(inputStringList);

    int score = cave.placeAllSands();
    cave.printMap();

    cout << "Score: " << score << "\n";

}

void day14Part2(const list<string> &inputStringList) {
    CaveCrossSection cave(inputStringList, true);

    int score = cave.placeAllSands();
    cave.printMap();
    cout << "Score: " << score << "\n";
}

int mainDay14() {
    initDay(14, &day14Part1, &day14Part2);
    return 14;
}