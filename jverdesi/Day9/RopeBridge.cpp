//
// Created by jacob on 12/11/2022.
//
#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <fstream>
#include "../Utils/InitDay.h"
#include "RopeBridge.h"
#include "../Utils/FileReader.h"

using namespace std;

void update_current_knot_position(pair<int, int> &curr_knot, pair<int, int> &prev_knot) {
    int x_diff = prev_knot.first - curr_knot.first;
    int y_diff = prev_knot.second - curr_knot.second;
    if (abs(x_diff) == 2)
        x_diff = x_diff + (2 * (x_diff < 0)) - 1;
    if (abs(y_diff) == 2)
        y_diff = y_diff + (2 * (y_diff < 0)) - 1;
    if (abs(prev_knot.second - curr_knot.second) == 2 or abs(prev_knot.first - curr_knot.first) == 2) {
        curr_knot.first = curr_knot.first + x_diff;
        curr_knot.second = curr_knot.second + y_diff;
    }
}

void next_rope_state(vector<pair<int, int>> &knotList, char direction) {
    for (int i = 0; i < knotList.size(); i++) {
        pair<int, int> &curr_knot = knotList[i];
        if (i == 0) {
            switch (direction) {
                case 'R':
                    curr_knot.first++;
                    break;
                case 'L':
                    curr_knot.first--;
                    break;
                case 'U':
                    curr_knot.second--;
                    break;
                case 'D':
                    curr_knot.second++;
                    break;
            }
        } else {
            pair<int, int> &prev_knot = knotList[i - 1];
            update_current_knot_position(curr_knot, prev_knot);

        }
    }

}

set<pair<int, int>> get_visited_set(const list<string> &inputStringList, int num_knots) {
    vector<pair<int, int>> knotList(num_knots, pair(0, 0));
    set<pair<int, int>> tailVisited;
    for (string line: inputStringList) {
        if (!line.empty()) {
            string direction = strtok(line.data(), " ");
            int distance = stoi(strtok(nullptr, " "));
            int stepsRemaining = distance;
            while (stepsRemaining > 0) {
                next_rope_state(knotList, direction[0]);

                tailVisited.insert(knotList.back());
                stepsRemaining--;
            }
        }
    }
    return tailVisited;
}

void day9Part1(const list<string> &inputStringList) {

    cout << "Number of tail positions: " << get_visited_set(inputStringList, 2).size() << '\n';
}


void day9Part2(const list<string> &inputStringList) {

    cout << "Number of tail positions: " << get_visited_set(inputStringList, 10).size() << '\n';

}

vector<vector<char>>
makeDynamicBoard(vector<pair<int, int>> knotList) {

    int min_x = min_element(knotList.begin(), knotList.end(),
                            [](const auto &lhs, const auto &rhs) { return lhs.first < rhs.first; })->first;
    int max_x = max_element(knotList.begin(), knotList.end(),
                            [](const auto &lhs, const auto &rhs) { return lhs.first < rhs.first; })->first;
    int min_y = min_element(knotList.begin(), knotList.end(),
                            [](const auto &lhs, const auto &rhs) { return lhs.second < rhs.second; })->second;
    int max_y = max_element(knotList.begin(), knotList.end(),
                            [](const auto &lhs, const auto &rhs) { return lhs.second < rhs.second; })->second;
    int width = max_x - min_x + 1;
    int height = max_y - min_y + 1;
    vector<vector<char>> board(height, vector<char>(width, '.'));
    int knotIdx = 0;
    for (pair<int, int> knot: knotList) {
        int knot_x = knot.first - min_x;
        int knot_y = knot.second - min_y;
        if (board[knot_y][knot_x] == '.') {
            if (knotIdx == 0) {
                board[knot_y][knot_x] = 'H';
            } else if (knotIdx == knotList.size() - 1) {
                board[knot_y][knot_x] = 'T';
            } else
                board[knot_y][knot_x] = '#';
                // board[knot_y][knot_x] = (char)(knotIdx+48);

        }
        knotIdx++;
    }
    return board;

}

vector<vector<char>> visited_tail_board(const list<string> &inputStringList, int num_knots) {
    set<pair<int, int>> tailVisited = get_visited_set(inputStringList, num_knots);
  //  cout << "Number of tail positions: " << tailVisited.size() << " With " << num_knots << " Knots " << '\n';

    vector<pair<int, int>> visited(tailVisited.begin(), tailVisited.end());
    return makeDynamicBoard(visited);
}

void write_board_to_file(const vector<vector<char>> &board, const string &filepath) {
    ofstream fileStream(filepath);
    if (fileStream.is_open()) {
        for (const auto &row: board) {
            for (auto col: row) {
                if(col=='.')
                    fileStream << "\u2591";
                if(col=='#')
                    fileStream << "\u2593";

            }
            fileStream << "\n";
        }
        fileStream.close();
    }
}

void extra_credit() {
    string filepathInputData = "../Data/inputDay" + to_string(9) + ".txt";
    const list<string> &inputStringList = readInputFile(filepathInputData.c_str());
    vector<int> knotSizes = {2, 4, 8, 16, 32};
    for(auto knotSize:knotSizes) {
        string filePath = "../Day9/outputBoards/" + to_string(knotSize) + "Knots.txt";
        write_board_to_file(visited_tail_board(inputStringList, knotSize), filePath);
    }

}


int mainDay9() {
    initDay(9, &day9Part1, &day9Part2);
    //extra_credit();
    return 0;
}