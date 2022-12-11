//
// Created by jacob on 12/11/2022.
//
#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <bitset>
#include "../Utils/InitDay.h"
#include "TreetopTreeHouse.h"

using namespace std;
const int forest_size = 99;

bitset<forest_size> getOutsideVisibleTrees(const int *row) {
    int visibleLeft = -1;
    int visibleRight = -1;
    bitset<forest_size> visible;

    for (int index = 0; index < forest_size; index++) {
        visible[forest_size - index - 1] = visible[forest_size - index - 1] || row[index] > visibleLeft;
        if (row[index] > visibleLeft)
            visibleLeft = row[index];
        visible[index] = visible[index] || row[forest_size - index - 1] > visibleRight;
        if (row[forest_size - index - 1] > visibleRight)
            visibleRight = row[forest_size - index - 1];
    }
    return visible;
}

vector<int> getScenicScore(const int *row) {
    vector<int> scenicScoreList;

    for (int index = 0; index < forest_size; index++) {
        int num_visible_left = 1;
        int left_idx = index - 1;
        if (index == 0)
            num_visible_left = 0;
        while (left_idx > 0 and row[index] > row[left_idx]) {
            num_visible_left++;
            left_idx--;
        }
        int num_visible_right = 1;
        int right_idx = index + 1;
        if (index == forest_size - 1)
            num_visible_right = 0;
        while (right_idx < forest_size - 1 and row[index] > row[right_idx]) {
            num_visible_right++;
            right_idx++;
        }

        scenicScoreList.push_back(num_visible_left * num_visible_right);

    }
    return scenicScoreList;
}

void day8Part1(const list<string> &inputStringList) {
    int forestRow[forest_size][forest_size];
    int forestColumn[forest_size][forest_size];

    int strrow = 0;
    for (const string &line: inputStringList) {
        int strcolumn = 0;
        for (auto &ch: line) {
            forestRow[strrow][strcolumn] = (int) (unsigned) ch - 48;
            forestColumn[strcolumn][strrow] = (int) (unsigned) ch - 48; //transpose
            strcolumn++;
        }
        strrow++;
    }
    bitset<forest_size> rowVisible[forest_size];
    bitset<forest_size> columnVisible[forest_size];

    for (int i = 0; i < forest_size; i++) {
        rowVisible[i] = getOutsideVisibleTrees(forestRow[i]);
        columnVisible[i] = getOutsideVisibleTrees(forestColumn[i]);
    }
    bitset<forest_size> totalOutsideVisible[forest_size];

    for (int row = 0; row < forest_size; row++) {
        for (int column = 0; column < forest_size; column++) {
            totalOutsideVisible[row][column] =
                    rowVisible[row][column] || columnVisible[forest_size - 1 - column][forest_size - 1 - row];
        }
    }
    size_t totalBits = 0;
    for (auto totalrowVisible: totalOutsideVisible) {
        //cout << totalrowVisible << '\n';
        totalBits += totalrowVisible.count();
    }
    cout << "Total visible Trees from outside: " << totalBits << '\n';

}

void day8Part2(const list<string> &inputStringList) {
    size_t length = inputStringList.front().length();
    int forestRow[length][length];
    int forestColumn[length][length];

    int strrow = 0;
    for (const string &line: inputStringList) {
        int strcolumn = 0;
        for (auto &ch: line) {
            forestRow[strrow][strcolumn] = (int) (unsigned) ch - 48;
            forestColumn[strcolumn][strrow] = (int) (unsigned) ch - 48; //transpose
            strcolumn++;
        }
        strrow++;
    }
    vector<vector<int>> rowScenicScore;
    vector<vector<int>> columnScenicScore;

    for (int i = 0; i < length; i++) {
        rowScenicScore.push_back(getScenicScore(forestRow[i]));
        columnScenicScore.push_back(getScenicScore(forestColumn[i]));
    }
    int totalScenicScore[length][length];
    int maxScenic=0;
    for (int row = 0; row < forest_size ; row++) {
        for (int column = 0; column < forest_size ; column++) {
            int curr_tree_scenic= rowScenicScore[row][column] * columnScenicScore[ column][row];
            totalScenicScore[row][column] =curr_tree_scenic;
            if(curr_tree_scenic>maxScenic)
                maxScenic=curr_tree_scenic;

        }
    }
//    for (const auto &totalrowScenic: totalScenicScore) {
//        for (const auto &totalcolScenic: totalrowScenic)
//            cout << totalcolScenic << ' ';
//        cout << '\n';
//    }
    cout << "Highest Scenic score: " << maxScenic << "\n";
}

int mainDay8() {
    initDay(8, &day8Part1, &day8Part2);
    return 0;
}